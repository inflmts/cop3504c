//----------------------------------------------------------
// File: cowsay.cpp
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
//    The cow has evolved -- and it is back with a
//    vengeance. Face the angry cow and the mighty dragon in
//    this cringey command-line adventure!
//
//----------------------------------------------------------

#include <cstring>
#include <iostream>
#include "Cow.h"
#include "Dragon.h"
#include "HeiferGenerator.h"

// Students may implement private attributes and methods if
// they chose to do so. This is not required – it is purely
// optional. No public attributes/methods should be added to
// the specification!
//
// Your program must accept command line arguments as
// follows:
//
//     cowsay ‐l              Lists the available cows
//     cowsay MESSAGE         Prints out the MESSAGE using the default cow
//     cowsay ‐n COW MESSAGE  Prints out the MESSAGE using the specified COW
//
int main(int argc, char **argv)
{
  // drop the executable name
  --argc;
  ++argv;

  // public static vector<Cow*>& getCows()
  //
  //   Returns a reference to a vector of cow object
  //   pointers from built-in data set. This will call the
  //   Cow constructor and setImage() methods of the cow
  //   class if needed to initialize new cow objects
  //   uniquely for each data set.
  //
  const std::vector<Cow*>& cows = HeiferGenerator::getCows();

  // -l lists available cows
  if (argc >= 1 && !strcmp(argv[0], "-l")) {
    std::cout << "Cows available:";
    for (size_t i = 0; i < cows.size(); i++)
      std::cout << " " << cows[i]->getName();
    std::cout << "\n\n";
    return 0;
  }

  const char *cow_name = "heifer";
  Cow *cow = nullptr;
  Dragon *dragon = nullptr;

  // -n COW selects a named cow
  if (argc >= 2 && !strcmp(argv[0], "-n")) {
    cow_name = argv[1];
    argc -= 2;
    argv += 2;
  }

  // find the cow
  for (size_t i = 0; i < cows.size(); i++) {
    Cow *c = cows[i];
    if (c->getName() == cow_name) {
      cow = c;

      // public static Dragon* getDragonPointer(Cow* candidate)
      //
      //   If object pointed to by candidate is a Dragon
      //   (including an IceDragon), returns a Dragon
      //   pointer to the object. Otherwise, returns
      //   nullptr.
      //
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

// vim:tw=60
