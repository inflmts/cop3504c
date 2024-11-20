#include <cstdlib>
#include <iostream>
#include "memer.h"

const char *const usage = "\
usage: memeify <image> <top-text> [<bottom-text> [TX TY BX BY]]\n\
";

int main(int argc, char **argv)
{
  if (argc < 3 || argc > 8) {
    std::cerr << usage;
    return 2;
  }

  const char *base_filename = argv[1];
  const char *top_text = argv[2];
  const char *bottom_text = argc > 3 ? argv[3] : "";
  int tx = argc > 4 ? atoi(argv[4]) : -1;
  int ty = argc > 5 ? atoi(argv[5]) : -1;
  int bx = argc > 6 ? atoi(argv[6]) : -1;
  int by = argc > 7 ? atoi(argv[7]) : -1;
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

  while (window.isOpen()) {
    // clear the window
    window.clear();
    window.draw(meme_sprite);
    window.display();

    // process events
    sf::Event event;
    while (window.waitEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::Resized) {
        break;
      }
    }
  }

  return 0;
}
