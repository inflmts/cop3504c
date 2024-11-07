#include "Cow.h"

Cow::Cow(const std::string& name):
  name_(name)
{}

std::string& Cow::getName()
{
  return name_;
}

std::string& Cow::getImage()
{
  return image_;
}

void Cow::setImage(const std::string& image)
{
  image_ = image;
}
