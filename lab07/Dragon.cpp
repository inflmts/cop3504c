//----------------------------------------------------------
// File: Dragon.cpp
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

#include "Dragon.h"

Dragon::Dragon(const std::string& _name, const std::string& _image):
  Cow(_name)
{
  setImage(_image);
}

bool Dragon::canBreatheFire()
{
  return true;
}

// vim:tw=60
