#ifndef COWSAY_ICEDRAGON_H
#define COWSAY_ICEDRAGON_H

#include <string>
#include "Dragon.h"

class IceDragon: public Dragon
{
public:
  IceDragon(const std::string& name, const std::string& image);
  bool canBreatheFire();
};

#endif
