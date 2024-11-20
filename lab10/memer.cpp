#include <cstdlib>
#include "memer.h"

sf::Image generateMeme(sf::Image base, sf::String top_text, sf::String bottom_text,
                       int tx, int ty, int bx, int by)
{
  sf::Texture base_texture;
  if (!base_texture.loadFromImage(base))
    exit(-1);
  sf::Vector2u base_size = base_texture.getSize();
  sf::Sprite base_sprite(base_texture);

  if (tx < 0) tx = base_size.x / 2;
  if (ty < 0) ty = base_size.y / 3;
  if (bx < 0) bx = base_size.x / 2;
  if (by < 0) by = 2 * base_size.y / 3;

  sf::Font font;
  if (!font.loadFromFile("Cave-Story.ttf"))
    exit(-1);
  sf::Vector2f size;
  sf::Text ttext(top_text, font);
  size = ttext.getLocalBounds().getSize();
  ttext.setPosition(tx - (int)size.x / 2, ty - (int)size.y / 2);
  sf::Text btext(bottom_text, font);
  size = btext.getLocalBounds().getSize();
  btext.setPosition(bx - (int)size.x / 2, by - (int)size.y / 2);

  sf::RenderTexture canvas;
  canvas.create(base_size.x, base_size.y);
  canvas.draw(base_sprite);
  canvas.draw(ttext);
  canvas.draw(btext);
  canvas.display();
  return canvas.getTexture().copyToImage();
}
