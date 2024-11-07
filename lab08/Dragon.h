#ifndef COWSAY_DRAGON_H
#define COWSAY_DRAGON_H

#include <string>
#include "Cow.h"

class Dragon: public Cow
{
public:
  Dragon(const std::string& name, const std::string& image);
  virtual bool canBreatheFire();
};

#endif
