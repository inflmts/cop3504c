//----------------------------------------------------------
// File: Dragon.h
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

#ifndef DRAGON_H
#define DRAGON_H

#include <string>
#include "Cow.h"

//**********************************************************
// Dragon Class
//**********************************************************
//
// The Dragon class must be derived from the Cow class and
// must make all its methods available. You may mark any
// additional methods virtual as necessary. In addition,
// Dragon must provide the following methods:
//
class Dragon: public Cow
{
  public:
    // Constructor; creates new Dragon object with given
    // name and image. This must be its only public
    // constructor!
    Dragon(const std::string& _name, const std::string& _image);

    // This method should exist in every Dragon class. For
    // the default Dragon type, it should always return
    // true.
    virtual bool canBreatheFire();
};

#endif

// vim:tw=60
