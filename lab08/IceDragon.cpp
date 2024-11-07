#include "IceDragon.h"

IceDragon::IceDragon(const std::string& name, const std::string& image):
  Dragon(name, image)
{}

bool IceDragon::canBreatheFire()
{
  return false;
}
