#ifndef COWSAY_FILECOW_H
#define COWSAY_FILECOW_H

#include <string>
#include "Cow.h"

//----------------------------------------------------------------------------
// FileCow Class
//----------------------------------------------------------------------------
//
// The FileCow class must be derived from the Cow class. In addition, FileCow
// must add the following behavior:
//
class FileCow: public Cow
{
public:
  // Constructor; creates a new FileCow object with the given name and an
  // image loaded from filename. If the file cannot be loaded, it should throw
  // a new std::ifstream::failure exception object with the message
  // "MOOOOO!!!!!!". This should be the only public constructor for the
  // FileCow class!
  FileCow(const std::string& name, const std::string& filename);

  // Should throw a new std::runtime_error exception object with message
  // "Cannot reset FileCow Image".
  void setImage(const std::string& image);
};

#endif
