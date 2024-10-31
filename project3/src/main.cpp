//////////////////////////////////////////////////////////////////////////////
// File: main.cpp
//
//  ##########################################################################
//    Project 3: Image Processing
//  ##########################################################################
//
//    Author: Daniel Li
//    Course: COP3504C
//    Section: 25452
//    Date: Oct 29 2024
//
//    "Let him who will move the world
//     first move himself."
//
//////////////////////////////////////////////////////////////////////////////

#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

class Image
{
  unsigned int width_;
  unsigned int height_;
  unsigned char *data_;
  size_t data_len_;
  unsigned char *data_end_;

  void init(unsigned int width, unsigned int height)
  {
    width_ = width;
    height_ = height;
    data_len_ = 3 * width_ * height_;
    data_ = new unsigned char[data_len_];
    data_end_ = data_ + data_len_;
  }

  void init_from_stream(std::istream& stream)
  {
    Header header;
    stream.read(reinterpret_cast<char *>(&header), sizeof(header));
    init((unsigned int)header.width[0] | (unsigned int)header.width[1] << 8,
         (unsigned int)header.height[0] | (unsigned int)header.height[1] << 8);
    stream.read(reinterpret_cast<char *>(data_), data_len_);
  }

public:
  struct Header
  {
    unsigned char id_length;
    unsigned char color_map_type;
    unsigned char data_type_code;
    unsigned char color_map_origin[2];
    unsigned char color_map_length[2];
    unsigned char color_map_depth;
    unsigned char x_origin[2];
    unsigned char y_origin[2];
    unsigned char width[2];
    unsigned char height[2];
    unsigned char bits_per_pixel;
    unsigned char image_descriptor;
  };

  static_assert(sizeof(Header) == 18);

  Image(unsigned int width, unsigned int height)
  {
    init(width, height);
  }

  Image(const Image& src)
  {
    init(src.width_, src.height_);
    std::memcpy(data_, src.data_, data_len_);
  }

  Image(std::istream& stream)
  {
    init_from_stream(stream);
  }

  Image(const char *filename)
  {
    std::ifstream stream(filename, std::ios_base::binary);
    init_from_stream(stream);
  }

  ~Image()
  {
    delete[] data_;
  }

  unsigned int width() const { return width_; }
  unsigned int height() const { return height_; }
  const unsigned char *data() const { return data_; }
  unsigned char *data() { return data_; }
  const unsigned char *data_end() const { return data_end_; }
  unsigned char *data_end() { return data_end_; }

  void write(std::ostream& stream) const
  {
    Header header{};
    header.data_type_code = 2;
    header.width[0] = width_;
    header.width[1] = width_ >> 8;
    header.height[0] = height_;
    header.height[1] = height_ >> 8;
    header.bits_per_pixel = 24;
    stream.write(reinterpret_cast<const char *>(&header), sizeof(header));
    stream.write(reinterpret_cast<const char *>(data_), data_len_);
  }

  void write(const char *filename) const
  {
    std::ofstream stream(filename, std::ios_base::binary);
    write(stream);
  }

  void multiply(const Image& src)
  {
    for (unsigned char *p = data_, *q = src.data_; p < data_end_; p++, q++)
      // this ensures that 128/255 rounds up and 127/255 rounds down
      *p = ((static_cast<unsigned int>(*p) * (*q)) + 127) / 255;
  }

  void subtract(const Image& src)
  {
    for (unsigned char *p = data_, *q = src.data_; p < data_end_; p++, q++)
      *p = *p > *q ? *p - *q : 0;
  }

  void screen(const Image& src)
  {
    for (unsigned char *p = data_, *q = src.data_; p < data_end_; p++, q++)
      *p = 255 - (static_cast<unsigned int>(255 - *p) * (255 - *q) + 127) / 255;
  }

  void overlay(const Image& src)
  {
    for (unsigned char *p = data_, *q = src.data_; p < data_end_; p++, q++)
      *p = *p < 128
        ? ((2 * static_cast<unsigned int>(*p) * (*q)) + 127) / 255
        : 255 - ((2 * static_cast<unsigned int>(255 - *p) * (255 - *q)) + 127) / 255;
  }

  void copy(const Image& src, unsigned int tx, unsigned int ty)
  {
    for (unsigned int r = 0; r < src.height_; r++)
      std::memcpy(data_ + 3 * ((ty + r) * width_ + tx), src.data_ + 3 * r * src.width_, 3 * src.width_);
  }

  bool operator==(const Image& other) const
  {
    return width_ == other.width_
        && height_ == other.height_
        && !std::memcmp(data_, other.data_, data_len_);
  }
};

//----------------------------------------------------------------------------
// Tasks
//----------------------------------------------------------------------------
//
// This assignment is broken into 10 different parts, each of which is worth a
// small portion of the overall grade. For each of these tasks you will:
//
//     1. Load one or more files from the `input` folder.
//     2. Perform some operation(s) on the loaded file(s).
//     3. Write the results to a new .TGA file (named part#.tga) in the
//        `output` folder. The `examples` folder has completed versions which
//        you can use to test against your files. If your file is identical to
//        its counterpart in the examples folder, you’re done with that part!
//

struct Task
{
  const char *name;
  const char **files;
  void (*run)();
};

static const Task tasks[] = {

  // Use Multiply blending mode to combine "layer1.tga" (top layer) with
  // "pattern1.tga" (bottom).
  {
    "part1",
    nullptr,
    [] {
      Image dest("input/pattern1.tga");
      Image src("input/layer1.tga");
      dest.multiply(src);
      dest.write("output/part1.tga");
    }
  },

  // Use the Subtract blending mode to combine "layer2.tga" (top layer) with
  // "car.tga" (bottom layer). This mode subtracts the top layer from the
  // bottom layer.
  {
    "part2",
    nullptr,
    [] {
      Image dest("input/car.tga");
      Image src("input/layer2.tga");
      dest.subtract(src);
      dest.write("output/part2.tga");
    }
  },

  // Use the Multiply blending mode to combine "layer1.tga" with
  // "pattern2.tga", and store the results temporarily. Load the image
  // "text.tga" and, using that as the top layer, combine it with the previous
  // results of layer1/pattern2 using the Screen blending mode.
  {
    "part3",
    nullptr,
    [] {
      Image dest("input/pattern2.tga");
      Image layer("input/layer1.tga");
      Image text("input/text.tga");
      dest.multiply(layer);
      dest.screen(text);
      dest.write("output/part3.tga");
    }
  },

  // Multiply "layer2.tga" with "circles.tga", and store it. Load
  // "pattern2.tga" and, using that as the top layer, combine it with the
  // previous result using the Subtract blending mode.
  {
    "part4",
    nullptr,
    [] {
      Image dest("input/circles.tga");
      Image layer("input/layer2.tga");
      Image pattern("input/pattern2.tga");
      dest.multiply(layer);
      dest.subtract(pattern);
      dest.write("output/part4.tga");
    }
  },

  // Combine "layer1.tga" (as the top layer) with "pattern1.tga" using the
  // Overlay blending mode.
  {
    "part5",
    nullptr,
    [] {
      Image dest("input/pattern1.tga");
      Image src("input/layer1.tga");
      dest.overlay(src);
      dest.write("output/part5.tga");
    }
  },

  // Load "car.tga" and add 200 to the green channel.
  {
    "part6",
    nullptr,
    [] {
      Image dest("input/car.tga");
      unsigned char *ptr = dest.data() + 1;
      unsigned char *end = dest.data_end();
      while (ptr < end) {
        *ptr = *ptr < 55 ? *ptr + 200 : 255;
        ptr += 3;
      }
      dest.write("output/part6.tga");
    }
  },

  // Load "car.tga" and scale (multiply) the red channel by 4, and the blue
  // channel by 0. This will increase the intensity of any red in the image,
  // while negating any blue it may have.
  {
    "part7",
    nullptr,
    [] {
      Image dest("input/car.tga");
      unsigned char *data = dest.data();
      unsigned char *end = dest.data_end();
      while (data < end) {
        *data = 0;
        data += 2;
        *data = *data < 64 ? *data * 4 : 255;
        data++;
      }
      dest.write("output/part7.tga");
    }
  },

  // Load "car.tga" and write each channel to a separate file: the red channel
  // should be "part8_r.tga", the green channel should be "part8_g.tga", and
  // the blue channel should be "part8_b.tga"
  {
    "part8",
    (const char *[]){ "part8_r.tga", "part8_g.tga", "part8_b.tga" },
    [] {
      Image src("input/car.tga");
      Image destb(src.width(), src.height());
      Image destg(src.width(), src.height());
      Image destr(src.width(), src.height());

      unsigned char *data = src.data();
      unsigned char *end = src.data_end();
      unsigned char *datab = destb.data();
      unsigned char *datag = destg.data();
      unsigned char *datar = destr.data();

      while (data < end) {
        datab[0] = datab[1] = datab[2] = data[0];
        datag[0] = datag[1] = datag[2] = data[1];
        datar[0] = datar[1] = datar[2] = data[2];
        data += 3;
        datab += 3;
        datag += 3;
        datar += 3;
      }

      destb.write("output/part8_b.tga");
      destg.write("output/part8_g.tga");
      destr.write("output/part8_r.tga");
    }
  },

  // Load "layer_red.tga", "layer_green.tga" and "layer_blue.tga", and combine
  // the three files into one file. The data from "layer_red.tga" is the red
  // channel of the new image, layer_green is green, and layer_blue is blue.
  {
    "part9",
    nullptr,
    [] {
      Image srcb("input/layer_blue.tga");
      Image srcg("input/layer_green.tga");
      Image srcr("input/layer_red.tga");
      Image dest(srcb.width(), srcb.height());

      unsigned char *datab = srcb.data();
      unsigned char *datag = srcg.data();
      unsigned char *datar = srcr.data();
      unsigned char *data = dest.data();
      unsigned char *end = dest.data_end();

      while (data < end) {
        *(data++) = datab[0];
        *(data++) = datag[0];
        *(data++) = datar[0];
        datab += 3;
        datag += 3;
        datar += 3;
      }

      dest.write("output/part9.tga");
    }
  },

  // Load "text2.tga", and rotate it 180 degrees, flipping it upside down.
  // This is easier than you think! Try diagramming the data of an image (such
  // as earlier in this document). What would the data look like if you
  // flipped it? Now, how to write some code to accomplish that...
  {
    "part10",
    nullptr,
    [] {
      Image dest("input/text2.tga");
      unsigned char *a = dest.data();
      unsigned char *b = dest.data_end() - 3;
      unsigned char tmp[3];
      while (a < b) {
        std::memcpy(tmp, a, 3);
        std::memcpy(a, b, 3);
        std::memcpy(b, tmp, 3);
        a += 3;
        b -= 3;
      }
      dest.write("output/part10.tga");
    }
  },

  //--------------------------------------------------------------------------
  // Extra Credit
  //--------------------------------------------------------------------------
  //
  // Additional Processing (5 points): Create a new file that is the
  // combination of car.tga, circles.tga, pattern1.tga, and text.tga. Each
  // source image will be in a quadrant of the final image, and the result
  // should look like the image in the instructions. The original images
  // should not be modified in any way; the final image will have to be large
  // enough to accommodate all of them.
  {
    "extracredit",
    nullptr,
    [] {
      Image dest(1024, 1024);
      Image car("input/car.tga");
      Image circles("input/circles.tga");
      Image pattern("input/pattern1.tga");
      Image text("input/text.tga");
      dest.copy(car, 0, 512);
      dest.copy(circles, 512, 512);
      dest.copy(pattern, 512, 0);
      dest.copy(text, 0, 0);
      dest.write("output/extracredit.tga");
    }
  }

};

constexpr size_t num_tasks = sizeof(tasks) / sizeof(struct Task);

int list_tasks()
{
  for (size_t i = 0; i < num_tasks; i++) {
    const Task& task = tasks[i];
    std::cout << task.name << "\n";
  }
  return 0;
}

static inline create_directory(const char *pathname) {
#ifdef _WIN32
  return mkdir(pathname);
#else
  return mkdir(pathname, 0777);
#endif
}

int main(int argc, char **argv)
{
  bool test_mode = false;

  int opt;
  opterr = false;
  while ((opt = getopt(argc, argv, "tl")) != -1) {
    switch (opt) {
      case 't':
        test_mode = true;
        break;
      case 'l':
        return list_tasks();
      case ':':
        std::cerr << "error: option requires an argument: -" << (char)optopt << "\n";
        return -1;
      default:
        std::cerr << "error: invalid option: -" << (char)optopt << "\n"
                  << "usage:\n"
                  << "  image-processor [-t] [tasks...]\n"
                  << "  image-processor -l\n";
        return -1;
    }
  }

  argc -= optind;
  argv += optind;

  // create output directory
  if (create_directory("output") && errno != EEXIST) {
    std::cerr << "Failed to create output directory: " << strerror(errno) << "\n";
    return 1;
  }

  unsigned long disabled_tasks = 0;
  static_assert(num_tasks <= 8 * sizeof(disabled_tasks));

  // fill out bit field with requested tasks
  if (argc) {
    disabled_tasks = -1ul;
    for (int k = 0; k < argc; k++)
      for (size_t i = 0; i < num_tasks; i++)
        if (!strcmp(argv[k], tasks[i].name))
          disabled_tasks &= ~(1ul << i);
  }

  std::string default_output_file;

  for (size_t i = 0; i < num_tasks; i++) {
    const Task& task = tasks[i];

    if (disabled_tasks & (1ul << i))
      continue;

    std::cout << "\e[1mExecuting task: " << task.name << "\e[0m\n";
    task.run();

    if (test_mode) {
      const char **files = task.files;

      if (!files) {
        default_output_file = task.name;
        default_output_file += ".tga";
        files = (const char *[]){ default_output_file.c_str(), nullptr };
      }

      while (*files) {
        std::string output_file("output/");
        output_file += *files;

        std::string example_file("examples/EXAMPLE_");
        example_file += *files;

        Image output(output_file.c_str());
        Image example(example_file.c_str());
        std::cout << output_file << ": ";
        if (output == example)
          std::cout << "\e[1;32mpass\e[0m\n";
        else
          std::cout << "\e[1;31mfail\e[0m\n";

        ++files;
      }
    }
  }

  return 0;
}

// vim:tw=78:fo+=n
