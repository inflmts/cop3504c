//----------------------------------------------------------
// File: Cow.cpp
//
//  ########################################################
//    Lab 06: The Cow Strikes Back
//  ########################################################
//
//    Author: Daniel Li
//    Course: COP3504C
//    Section: 25452
//    Date: Oct 22 2024
//
//----------------------------------------------------------

#include "Cow.h"

Cow::Cow(const std::string& _name) : name(_name)
{}

std::string& Cow::getName()
{
  return name;
}

std::string& Cow::getImage()
{
  return image;
}

void Cow::setImage(const std::string& _image)
{
  image = _image;
}

// vim:tw=60
