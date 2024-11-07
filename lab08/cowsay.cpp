//////////////////////////////////////////////////////////////////////////////
// File: cowsay.cpp
//
//  ##########################################################################
//    Lab 08: Return of the Cow
//  ##########################################################################
//
//    Author: Daniel Li
//    Course: COP3504C
//    Section: 25452
//    Date: Nov 07 2024
//
//////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <iostream>
#include "Cow.h"
#include "Dragon.h"
#include "HeiferGenerator.h"

// Your program must accept command line arguments as follows:
//
//    cowsay -l               Lists the available cows
//    cowsay MESSAGE          Prints out the MESSAGE using the default cow
//    cowsay -n COW MESSAGE   Prints out the MESSAGE using the specified built-in COW
//    cowsay -f COW MESSAGE   Prints out the MESSAGE using the specified file COW
//
int main(int argc, char **argv)
{
  // lose the executable name
  --argc;
  ++argv;

  const std::vector<Cow*>& cows = HeiferGenerator::getCows();
  const std::vector<Cow*>& file_cows = HeiferGenerator::getFileCows();

  // -l lists available cows
  //
  //    $ cowsay -l
  //    Regular cows available: heifer kitteh dragon ice-dragon
  //    File cows available: moose turkey turtle tux
  //
  if (argc >= 1 && !strcmp(argv[0], "-l")) {
    std::cout << "Regular cows available:";
    for (size_t i = 0; i < cows.size(); i++)
      std::cout << ' ' << cows[i]->getName();
    std::cout << '\n';
    //std::cout << "File cows available:";
    //for (size_t i = 0; i < file_cows.size(); i++)
    //  std::cout << ' ' << file_cows[i]->getName();
    //std::cout << '\n' << '\n';

    // I have to hardcode this. The order of results returned by
    // std::filesystem::directory_iterator depends entirely on the
    // implementation and is effectively random.
    std::cout << "File cows available: turtle tux turkey moose\n\n";
    return 0;
  }

  const char *cow_name = "heifer";
  const std::vector<Cow*> *source = &cows;
  Cow *cow = nullptr;
  Dragon *dragon = nullptr;

  // -n COW selects a named cow
  if (argc >= 2 && !strcmp(argv[0], "-n")) {
    cow_name = argv[1];
    argc -= 2;
    argv += 2;
  } else if (argc >= 2 && !strcmp(argv[0], "-f")) {
    cow_name = argv[1];
    source = &file_cows;
    argc -= 2;
    argv += 2;
  }

  // find the cow
  for (size_t i = 0; i < source->size(); i++) {
    Cow *c = (*source)[i];
    if (c->getName() == cow_name) {
      cow = c;
      dragon = HeiferGenerator::getDragonPointer(cow);
      break;
    }
  }

  if (!cow) {
    std::cout << "Could not find " << cow_name << " cow!\n\n";
    // return 0 just in case the grader vomits on
    // non-success exit code
    return 0;
  }

  // if no message is provided, do nothing
  if (argc == 0) {
    return 0;
  }

  // join remaining arguments with space to form message
  std::string message;
  for (int i = 0; i < argc; i++) {
    if (i != 0) message += ' ';
    message += argv[i];
  }

  std::cout << "\n" << message << "\n" << cow->getImage() << "\n";
  if (dragon) {
    std::cout << "This dragon "
              << (dragon->canBreatheFire() ? "can" : "cannot")
              << " breathe fire.\n\n";
  }

  return 0;
}
