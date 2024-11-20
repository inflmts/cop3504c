#ifndef LAB10_MEMER_H
#define LAB10_MEMER_H

#include <SFML/Graphics.hpp>

// Takes in an base to be used as the base image. Returns a new sf::Image with
// topText drawn over it at location (topX, topY) in the provided font. If no
// coordinates are provided, topText should be centered horizontally and be
// 1/3 from the top of the image. If it is provided, bottomText is drawn at
// location (bottomX, bottomY). If provided, the tbottomText should be placed
// 1/3 from the bottom of the image.
//
// In general, adding text to an image will consist of the following steps:
//
//    1. Converting the Image into a Texture
//    2. Wrapping the Texture in a Sprite
//    3. Drawing the Sprite on a fresh & empty RenderTexture
//    4. Loading a Font, and using it to construct a Text element
//    5. Drawing the Text on the RenderTexture
//    6. Extracting an Image from a Texture, derived from the RenderTexture.
//
sf::Image generateMeme(sf::Image base, sf::String topText, sf::String bottomText = "",
                       int topX = -1, int topY = -1, int bottomX = -1, int bottomY = -1);

#endif
