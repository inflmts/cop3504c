#ifndef COWSAY_COW_H
#define COWSAY_COW_H

#include <string>

class Cow
{
  std::string name_;
  std::string image_;
public:
  Cow(const std::string& name);
  std::string& getName();
  std::string& getImage();
  virtual void setImage(const std::string& image);
};

#endif
