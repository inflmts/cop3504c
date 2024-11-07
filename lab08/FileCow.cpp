#include <fstream>
#include "FileCow.h"
#include <iostream>

FileCow::FileCow(const std::string& name, const std::string& filename):
  Cow(name)
{
  std::ifstream file(filename);
  std::string image;
  if (!file)
    throw std::ifstream::failure("MOOOOO!!!!!!");

  char buffer[1024];
  while (file.read(buffer, sizeof(buffer)))
    image.append(buffer, sizeof(buffer));
  image.append(buffer, file.gcount());
  Cow::setImage(image);
}

void FileCow::setImage(const std::string& image)
{
  throw std::runtime_error("Cannot reset FileCow Image");
}
