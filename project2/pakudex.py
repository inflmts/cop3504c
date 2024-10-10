############################################################
# File: pakudex.py
#
#   --------------------------------------------------------
#   Project 2: Pakudex
#   --------------------------------------------------------
#
#   Author: Daniel Li <li.daniel@ufl.edu>
#   Course: COP3504C
#   Section: 25452
#   Date: Oct 03-09, 2024
#
#   NOTE: This project concept is a work of satire. To state
#   what may or may not be obvious: we do not advise one to
#   go around imprisoning creatures in small receptacles
#   held in one's pockets and/or having them fight for
#   sport.
#
#   Pouch Creatures – abbreviated "Pakuri" – are the latest
#   craze sweeping elementary schools around the world. Tiny
#   magical creatures small enough to fit into one's trouser
#   pouches (with enough force applied, ‘natch) have begun
#   appearing all around the world in forests. They come in
#   all shapes colors. When stolen from their parents at a
#   young enough age, they can be kept in small spherical
#   cages (for their own good) easily carried by elementary
#   school children (though they are also popular with
#   adults). This has led to an unofficial catch phrase for
#   the phenomenon – "Gotta steal ‘em all!" – a play on the
#   abbreviation "Pakuri" (which doubles as Japanese slang
#   meaning "to steal"). Young children can then pit their
#   Pakuri against one another in battle for bragging rights
#   or to steal them from one another. (Don't worry – they
#   heal their wounds quickly!)
#
#   Of course, keeping track of all these critters can be a
#   real task, especially when you are trying to steal so
#   many of them at such a young age! You've decided to cash
#   in – hey, if you don't someone else will – on the
#   morally ambiguous phenomenon by developing an indexing
#   system – a Pakudex – for kids and adult participants.
#
############################################################

import os
from pakuri import Pakuri

# Echo all input if the environment variable PAKUDEX_ECHO_INPUT is set.
if 'PAKUDEX_ECHO_INPUT' in os.environ and len(os.environ['PAKUDEX_ECHO_INPUT']):
    _input = input
    def input(prompt):
        value = _input(prompt)
        print(value)
        return value

#---------------------------------------
# Pakudex Class
#---------------------------------------
#
#   The Pakudex class will contain all the Pakuri that you will encounter as
#   Pakuri objects.
#
class Pakudex:

    # __init__(self)
    # Default constructor; should prepare a new Pakudex object.
    def __init__(self):
        self.__pakuri = []

    def find_species(self, species):
        for pakuri in self.__pakuri:
            if pakuri.get_species() == species:
                return pakuri
        return None

    def find_species_index(self, species):
        for i, pakuri in enumerate(self.__pakuri):
            if pakuri.get_species() == species:
                return i
        return None

    # get_species_list(self) -> list[str]
    # Returns a list of names of the species of the critters as ordered in the
    # Pakudex; if there are no species added yet, this method should return
    # None.
    def get_species_list(self):
        if len(self.__pakuri) == 0:
            return None
        return [pakuri.get_species() for pakuri in self.__pakuri]

    # get_stats(self, species: str) -> list[int]
    # Returns an int list containing the level, CP, and HP of species at
    # indices 0, 1, and 2 respectively; if species is not in the Pakudex,
    # returns None.
    def get_stats(self, species):
        pakuri = self.find_species(species)
        if pakuri:
            return [pakuri.level, pakuri.cp, pakuri.hp]
        else:
            return None

    # sort_pakuri(self)
    # Sorts Pakuri objects in this Pakudex according to Python standard
    # lexicographical ordering of species name.
    def sort_pakuri(self):
        self.__pakuri.sort(key=lambda pakuri: pakuri.get_species())

    # add_pakuri(self, species: str, level: int) -> bool
    # Adds species to the Pakudex; if successful, return True, and False
    # otherwise (ie. the species is a duplicate).
    def add_pakuri(self, species, level):
        if self.find_species(species):
            return False
        self.__pakuri.append(Pakuri(species, level))
        return True

    # remove_pakuri(self, species: str) -> bool
    # Removes a species from the Pakudex; if successful, return True, and False
    # otherwise (ie. the species doesn't exist).
    def remove_pakuri(self, species):
        index = self.find_species_index(species)
        if index is None:
            return False
        self.__pakuri.pop(index)
        return True

    # evolve_species(self, species: str) -> bool
    # Attempts to evolve species within the Pakudex. This should double the
    # Pakuri's level and increment (increase by one) its attack. If successful,
    # return True, and False otherwise (ie. the species doesn't exist).
    def evolve_species(self, species):
        pakuri = self.find_species(species)
        if pakuri is None:
            return False

        # I see what you did here you sneaky bastards
        pakuri.level *= 2
        pakuri.set_attack(pakuri.get_attack() + 1)
        return True

    def interactive_list(self):
        species_list = self.get_species_list()
        if species_list is None:
            print('No Pakuri currently in the Pakudex!')
            return
        print('Pakuri in Pakudex:')
        for i, species in enumerate(species_list):
            print(f'{i + 1}. {species}')

    def interactive_show(self):
        species = input('Enter the name of the species to display: ')
        stats = self.get_stats(species)
        if stats is None:
            print('Error: No such Pakuri!')
            return
        print()
        print(f'Species: {species}')
        print(f'Level: {stats[0]}')
        print(f'CP: {stats[1]}')
        print(f'HP: {stats[2]}')

    # Adding Pakuri
    # When adding a Pakuri, a prompt should be displayed to read in the species
    # name, and a confirmation displayed following successful addition (or
    # failure).
    def interactive_add(self):
        species = input('Species: ')
        if self.find_species(species):
            print('Error: Pakudex already contains this species!')
            return
        while True:
            try:
                level = int(input('Level: '))
            except ValueError:
                print('Invalid level!')
                continue
            if level < 0:
                print('Level cannot be negative.')
                continue
            break
        # this shouldn't fail...
        ret = self.add_pakuri(species, level)
        assert ret
        print(f'Pakuri species {species} (level {level}) added!')

    # Removing Pakuri
    # The program should prompt for a species name and then remove the Pakuri
    # if it is in the Pakudex
    def interactive_remove(self):
        species = input('Enter the name of the Pakuri to remove: ')
        if self.remove_pakuri(species):
            print(f'Pakuri {species} removed.')
        else:
            print('Error: No such Pakuri!')

    # Evolve Pakuri
    # The program should prompt for a species and then cause the species to
    # evolve if it exists:
    def interactive_evolve(self):
        species = input('Enter the name of the species to evolve: ')
        if self.evolve_species(species):
            print(f'{species} has evolved!')
        else:
            print('Error: No such Pakuri!')

    def interactive_sort(self):
        self.sort_pakuri()
        print('Pakuri have been sorted!')

#---------------------------------------
# Entry Point
#---------------------------------------
#
#   When run as a program, the pakudex module should...
#
#       1) Display a welcome message
#       2) Prompt for input & conduct input error checking
#       3) Follow the output and formatting in this document
#       4) Not have print statements in the class method calls
#       5) Only run main() if invoked directly (i.e., check __name__)
#       6) Have no global variables
#
def main():
    pakudex = Pakudex()

    print('Welcome to Pakudex: Tracker Extraordinaire!')

    while True:
        print('''\

Pakudex Main Menu
-----------------
1. List Pakuri
2. Show Pakuri
3. Add Pakuri
4. Remove Pakuri
5. Evolve Pakuri
6. Sort Pakuri
7. Exit

''', end='')

        action = input('What would you like to do? ')
        print()

        match action:
            case '1': pakudex.interactive_list()
            case '2': pakudex.interactive_show()
            case '3': pakudex.interactive_add()
            case '4': pakudex.interactive_remove()
            case '5': pakudex.interactive_evolve()
            case '6': pakudex.interactive_sort()
            case '7': break
            case _: print('Unrecognized menu selection!')

    print('Thanks for using Pakudex! Bye!')

if __name__ == '__main__':
    main()
