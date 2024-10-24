//----------------------------------------------------------
// File: Cow.h
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

#ifndef COW_H
#define COW_H

#include <string>

//**********************************************************
// Cow Class
//**********************************************************
//
// The Cow class must have all the same methods as
// previously required, though students may add private
// methods.
//
class Cow
{
  private:
    std::string name;
    std::string image;
  public:
    Cow(const std::string& _name);
    std::string& getName();
    std::string& getImage();
    virtual void setImage(const std::string& _image);
};

#endif

// vim:tw=60
