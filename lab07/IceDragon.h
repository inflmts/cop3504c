//----------------------------------------------------------
// File: IceDragon.h
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

#ifndef ICEDRAGON_H
#define ICEDRAGON_H

#include <string>
#include "Dragon.h"

//**********************************************************
// IceDragon Class
//**********************************************************
//
// The IceDragon class must be derived from the Dragon class
// and must make all its methods available:
//
class IceDragon: public Dragon
{
  public:
    // Constructor; creates a new IceDragon object with the
    // given name and image. This should be the only public
    // constructor for the IceDragon class!
    IceDragon(const std::string& _name, const std::string& _image);

    // For the IceDragon type, this method should always
    // return false.
    bool canBreatheFire();
};

#endif

// vim:tw=60
