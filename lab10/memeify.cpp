//////////////////////////////////////////////////////////////////////////////
// File: memeify.cpp
//
//  --------------------------------------------------------------------------
//    Lab 10: Meme Generator
//  --------------------------------------------------------------------------
//
//    AKA SFML Hell
//
//    Author: Daniel Li
//    Course: COP3504C
//    Section: 25452
//    Date: Nov 21 2024
//
//////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include "memer.h"

const char *const usage = "\
usage: memeify <image> <top-text> [<bottom-text> [TX TY BX BY]]\n\
";

int main(int argc, char **argv)
{
  int opt;
  while ((opt = getopt(argc, argv, "h")) != -1) {
    switch (opt) {
      case 'h':
        std::cout << usage;
        return 0;
      default:
        std::cerr << usage;
        return 2;
    }
  }

  int i = optind;
  const char *base_filename = i < argc ? argv[i++] : "doge.jpg";
  const char *top_text = i < argc ? argv[i++] : "Look at that fatass";
  const char *bottom_text = i < argc ? argv[i++] : "";
  int tx = i < argc ? atoi(argv[i++]) : -1;
  int ty = i < argc ? atoi(argv[i++]) : -1;
  int bx = i < argc ? atoi(argv[i++]) : -1;
  int by = i < argc ? atoi(argv[i++]) : -1;
  sf::Image base;
  if (!base.loadFromFile(base_filename))
    return 1;
  sf::Image meme = generateMeme(base, top_text, bottom_text, tx, ty, bx, by);
  sf::Vector2u meme_size = meme.getSize();

  // create a window
  sf::RenderWindow window(sf::VideoMode(meme_size.x, meme_size.y), "Meme Generator");

  sf::Texture meme_texture;
  if (!meme_texture.loadFromImage(meme))
    return 1;

  sf::Sprite meme_sprite(meme_texture);

  // The executable should
  // 1) display the image in a window until the window is closed
  //
  //    ...or, in this case, if the user presses Q
  //
  while (window.isOpen()) {
    // clear the window
    window.clear();
    window.draw(meme_sprite);
    window.display();

    // process events
    // I wonder what happens if I use waitEvent()...
    sf::Event event;
    while (window.waitEvent(event)) {
      if (event.type == sf::Event::Closed
          || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Q)) {
        window.close();
      } else if (event.type == sf::Event::Resized) {
        break;
      }
    }
  }

  // and
  // 2) save the image with a new name based on the old one in the form of
  //    STEM-meme.EXT; e.g., if the original image was "doge.jpg", the new
  //    image saved should be "doge-meme.jpg".
  const char *dot = std::strrchr(base_filename, '.');
  std::string output_filename;
  if (dot)
    output_filename.assign(base_filename, dot - base_filename);
  else
    output_filename = base_filename;
  output_filename += "-meme.";
  output_filename += (dot + 1);
  // here we go
  if (!meme.saveToFile(output_filename))
    return 1;

  std::cout << "Meme successfully saved to '" << output_filename << "'\n";

  return 0;
}

// vim:tw=78
