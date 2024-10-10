############################################################
# File: pakuri.py
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
############################################################

import math

#---------------------------------------
# Pakuri Class
#---------------------------------------
#
#   This class will be the blueprint for the different critter objects that
#   you will create. You will need to store information about the critter's
#   species, attack level, defense level, and stamina. All variables storing
#   information about the critters must be private (inaccessible from outside
#   of the class per Python convention). We recommend (but do not mandate)
#   the following variable types and names:
#
#       __species: str
#       __level, __attack, __defense, __stamina: int
#
class Pakuri:

    # __init__(self, species: str, level: int)
    # This method should be the only constructor for this class. There should
    # not be a default constructor!
    def __init__(self, species, level):
        self.__species = species
        self.__level = level
        self.__attack = (len(species) * 7 + 11) % 16
        self.__defense = (len(species) * 5 + 17) % 16
        self.__stamina = (len(species) * 6 + 13) % 16

    # get_species(self) -> str
    # Returns the species of this critter
    def get_species(self):
        return self.__species

    # get_attack(self) -> int
    # Returns the attack value for this critter
    def get_attack(self):
        return self.__attack

    # get_defense(self) -> int
    # Returns the defense value for this critter
    def get_defense(self):
        return self.__defense

    # get_stamina(self) -> int
    # Returns the speed of this critter
    def get_stamina(self):
        return self.__stamina

    # set_attack(self, new_attack: int)
    # Changes the attack value for this critter to new_attack
    def set_attack(self, new_attack):
        self.__attack = new_attack

    # cp (read-only)
    # Calculates and returns the Pakuri object's combat power (CP).
    @property
    def cp(self):
        return math.floor(self.__attack * math.sqrt(self.__defense * self.__stamina) * self.__level * 0.08)

    # hp (read-only)
    # Calculates and returns the Pakuri object's health points (HP).
    @property
    def hp(self):
        return math.floor(self.__stamina * self.__level / 6)

    # level (read-write)
    # Gets, or sets, the Pakuri object's level attribute.
    @property
    def level(self):
        return self.__level

    @level.setter
    def level(self, level):
        self.__level = level

