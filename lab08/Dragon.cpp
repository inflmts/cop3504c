#include "Dragon.h"

Dragon::Dragon(const std::string& name, const std::string& image):
  Cow(name)
{
  setImage(image);
}

bool Dragon::canBreatheFire()
{
  return true;
}
