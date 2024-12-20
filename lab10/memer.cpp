//////////////////////////////////////////////////////////////////////////////
// File: memer.cpp
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
#include "memer.h"

sf::Image generateMeme(sf::Image base, sf::String top_text, sf::String bottom_text,
                       int tx, int ty, int bx, int by)
{
  // just follow the directions
  sf::Texture base_texture;
  if (!base_texture.loadFromImage(base))
    exit(-1);
  sf::Vector2u base_size = base_texture.getSize();
  sf::Sprite base_sprite(base_texture);

  // why do i have to do this
  if (tx < 0) tx = base_size.x / 2;
  if (ty < 0) ty = base_size.y / 3;
  if (bx < 0) bx = base_size.x / 2;
  if (by < 0) by = 2 * base_size.y / 3;

  // no no no no no no no no no no
  sf::Font font;
  if (!font.loadFromFile("Cave-Story.ttf"))
    exit(-1);
  sf::FloatRect bounds;
  sf::Text ttext(top_text, font);
  bounds = ttext.getLocalBounds();
  ttext.setPosition(tx - (int)(bounds.width / 2.0f), ty - (int)(bounds.height / 2.0f));
  sf::Text btext(bottom_text, font);
  bounds = btext.getLocalBounds();
  btext.setPosition(bx - (int)(bounds.width / 2.0f), by - (int)(bounds.height / 2.0f));

  // almost there!
  sf::RenderTexture canvas;
  canvas.create(base_size.x, base_size.y);
  canvas.draw(base_sprite);
  canvas.draw(ttext);
  canvas.draw(btext);
  canvas.display(); // shit why is this necessary
                    // fuck opengl
  return canvas.getTexture().copyToImage();
}











// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

// vim:tw=78
