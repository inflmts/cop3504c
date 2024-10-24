//----------------------------------------------------------
// File: IceDragon.cpp
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

#include "IceDragon.h"

IceDragon::IceDragon(const std::string& _name, const std::string& _image):
  Dragon(_name, _image)
{}

bool IceDragon::canBreatheFire()
{
  return false;
}

// vim:tw=60
