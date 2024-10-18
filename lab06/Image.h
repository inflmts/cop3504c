//------------------------------------------------------------------------------
// File: Image.h
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
//     This is here just for the requirement. I don't use it in scaler.cpp
//     because it doesn't have much functionality, and it doesn't memory-manage
//     the allocated image data at all.
//
//------------------------------------------------------------------------------

#ifndef IMAGE_H
#define IMAGE_H

class Image
{
public:
  Image(unsigned char *data);
  unsigned char *getImageData();
  unsigned char *getPixelData();
  unsigned char getWidth();
  unsigned char getHeight();
  void setImageData(unsigned char *data);
private:
  unsigned char *imageData;
};

#endif
