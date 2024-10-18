//------------------------------------------------------------------------------
// File: Image.cpp
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
//------------------------------------------------------------------------------

#include "Image.h"

Image::Image(unsigned char *data) :
  imageData(data)
{}

unsigned char *Image::getImageData()
{
  return imageData;
}

unsigned char *Image::getPixelData()
{
  return imageData + 2;
}

unsigned char Image::getWidth()
{
  return imageData[0];
}

unsigned char Image::getHeight()
{
  return imageData[1];
}

void Image::setImageData(unsigned char *data)
{
  imageData = data;
}
