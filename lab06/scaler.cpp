//------------------------------------------------------------------------------
// File: scaler.cpp
//
//   #########################################################################
//     LAB 06 :: Image Scaling
//   #########################################################################
//
//     Author: Daniel Li
//     Course: COP3504C
//     Section: 25452
//     Date: Oct 15 2024
//
//     This lab is designed to give students practice with memory manipulation
//     and function as a primer for Project 3.
//
//------------------------------------------------------------------------------

// Apparently, the autograder simply injects some code into this file to test
// the Image class. So we have to include this header file even if we don't use
// it.
#include "Image.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include "ConsoleGfx.h"

unsigned char *create_image(unsigned int width, unsigned int height)
{
  unsigned char *image_data = new unsigned char[2 + width * height];
  image_data[0] = width;
  image_data[1] = height;
  return image_data;
}

unsigned char *clone_image(unsigned char *image_data)
{
  unsigned int width = image_data[0];
  unsigned int height = image_data[1];
  unsigned int size = 2 + width * height;
  return static_cast<unsigned char *>(std::memcpy(new unsigned char[size], image_data, size));
}

unsigned char *scale_up(unsigned char *image_data, unsigned int orders)
{
  unsigned int width = image_data[0];
  unsigned int height = image_data[1];
  unsigned char *pixel_data = image_data + 2;

  while (width > 256u >> orders || height > 256u >> orders)
    --orders;
  if (orders == 0)
    return clone_image(image_data);

  unsigned int new_width = width << orders;
  unsigned int new_height = height << orders;
  unsigned char *new_image_data = create_image(new_width, new_height);
  unsigned char *new_pixel_data = new_image_data + 2;
  unsigned int i = 0;

  for (unsigned int y = 0; y < new_height; y++) {
    for (unsigned int x = 0; x < new_width; x++) {
      new_pixel_data[i++] = pixel_data[(y >> orders) * width + (x >> orders)];
    }
  }

  return new_image_data;
}

unsigned char *scale_down(unsigned char *image_data, unsigned int orders)
{
  unsigned int width = image_data[0];
  unsigned int height = image_data[1];
  unsigned char *pixel_data = image_data + 2;

  while (width >> orders == 0 || height >> orders == 0)
    --orders;
  if (orders == 0)
    return clone_image(image_data);

  unsigned int new_width = width >> orders;
  unsigned int new_height = height >> orders;
  unsigned char *new_image_data = create_image(new_width, new_height);
  unsigned char *new_pixel_data = new_image_data + 2;
  unsigned int i = 0;

  unsigned int histogram[16];

  for (unsigned int y = 0; y < new_height; y++) {
    for (unsigned int x = 0; x < new_width; x++) {
      // construct histogram of color frequencies
      std::memset(histogram, 0, sizeof(histogram));
      unsigned int sx_min = x << orders;
      unsigned int sx_max = (x + 1) << orders;
      unsigned int sy_min = y << orders;
      unsigned int sy_max = (y + 1) << orders;
      for (unsigned int sy = sy_min; sy < sy_max; sy++) {
        for (unsigned int sx = sx_min; sx < sx_max; sx++) {
          ++histogram[pixel_data[sy * width + sx]];
        }
      }

      // use histogram to determine most common color
      unsigned char max_color = 0;
      unsigned int max_freq = 0;
      for (unsigned int sy = sy_min; sy < sy_max; sy++) {
        for (unsigned int sx = sx_min; sx < sx_max; sx++) {
          unsigned char color = pixel_data[sy * width + sx];
          unsigned int freq = histogram[color];
          if (freq > max_freq) {
            max_color = color;
            max_freq = freq;
          }
        }
      }

      // set the new pixel value to the most common color
      new_pixel_data[i++] = max_color;
    }
  }

  return new_image_data;
}

//
// Returns a scaled version of the image data based on the orders of magnitude
// (i.e., powers of two to scale). The number of orders of magnitude should be
// in the range [-4, 4] (inclusive), which allows scaling down to 1/16 or up by
// a factor of 16 in each dimension. Do no implement this via recursive or
// iterative doubling; this takes twice as long as creating a new image one
// time, and it causes memory fragmentation.
//
// This function should never scale any image above 256 in width or height;
// instead, it should limit scaling such that the image is scaled up by a power
// of two but remains less than or equal to 256 in each dimension. Likewise, no
// image should be scaled below a height or width of one. To determine the
// color for reduced images, the number of colors of each pixel should be
// counted, and the most common color should be used. If there is a tie, the
// earliest pixel (by row, then by column) should be used. This function should
// allocate memory and return it to the caller; the caller is responsible for
// deallocation.
//
unsigned char *scaledImage(unsigned char *image_data, int orders)
{
  if (orders > 0)
    return scale_up(image_data, orders);
  else if (orders < 0)
    return scale_down(image_data, -orders);
  else
    return clone_image(image_data);
}

const char *const menu_text =
  "\n"
  "Scaler Menu\n"
  "-----------\n"
  "0. Exit\n"
  "1. Load File\n"
  "2. Load Test Image\n"
  "3. Display Image\n"
  "4. Enlarge Image\n"
  "5. Shrink Image\n"
  "6. Show Image Properties\n"
  "\n"
  "Select a Menu Option: "
;

// When the program is run via the main() method, the program should:
//
//     1) Fetch ConsoleGfx singleton via ConsoleGfx::getInstance()
//     2) Display the welcome message
//     3) Display color test (ConsoleGfx.testRainbow)
//     4) Display the menu
//     5) Prompt for input
//
int main()
{
  ConsoleGfx *gfx = ConsoleGfx::getInstance();
  unsigned char *image_data = nullptr;

  std::cout << "Welcome to the Image Scaler!\n\n"
            << "Displaying Spectrum Image:\n";
  gfx->displayImage(gfx->testRainbow);

  while (true) {
    std::string option;
    std::cout << menu_text;
    std::getline(std::cin, option);

    switch (option[0]) {
    case '0':
    case 'q':
    {
      goto end;
    }
    case '1':
    case 'l':
    {
      std::string filename;
      std::cout << "Enter name of file to load: ";
      std::getline(std::cin, filename);
      delete[] image_data;
      image_data = gfx->loadFile(filename);
      if (image_data)
        std::cout << "File loaded.\n";
      else
        std::cout << "Error: could not load file.\n";
      break;
    }
    case '2':
    case 't':
    {
      delete[] image_data;
      image_data = gfx->testImage;
      std::cout << "Test image data loaded.\n";
      break;
    }
    case '3':
    case 'p':
    {
      if (!image_data) {
        std::cout << "Error: no image loaded.\n";
        break;
      }

      gfx->displayImage(image_data);
      break;
    }
    case '4':
    case 'e':
    {
      if (!image_data) {
        std::cout << "Error: no image loaded.\n";
        break;
      }

      std::string input;
      std::cout << "Enter orders of magnitude for enlargement: ";
      std::getline(std::cin, input);
      unsigned int orders = std::stoul(input);
      unsigned char *new_image_data = scale_up(image_data, orders);
      delete[] image_data;
      image_data = new_image_data;
      std::cout << "Image enlarged!\n";
      break;
    }
    case '5':
    case 's':
    {
      if (!image_data) {
        std::cout << "Error: no image loaded.\n";
        break;
      }

      std::string input;
      std::cout << "Enter orders of magnitude for reduction: ";
      std::getline(std::cin, input);
      unsigned int orders = std::stoul(input);
      unsigned char *new_image_data = scale_down(image_data, orders);
      delete[] image_data;
      image_data = new_image_data;
      std::cout << "Image reduced!\n";
      break;
    }
    case '6':
    case 'i':
    {
      if (!image_data) {
        std::cout << "Error: no image loaded.\n";
        break;
      }

      unsigned int width = image_data[0];
      unsigned int height = image_data[1];
      std::cout << "Image Dimensions: (" << width << ", " << height << ")\n";
      break;
    }
    default:
    {
      std::cout << "Error: unrecognized command.\n";
    }
    }
  }

end:
  return 0;
}
