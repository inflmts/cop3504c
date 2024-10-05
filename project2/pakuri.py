########################################
# File: pakuri.py
#
#   ------------------------------------
#   Project 2: Pakudex
#   ------------------------------------
#
#   Author: Daniel Li
#   Course: COP3504C
#   Section: 25452
#   Date: Oct 03 2024
#
########################################

class Pakuri:
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

    #-----------------------------------
    # Required Properties
    #-----------------------------------

    # cp (read-only)
    # Calculates and returns the Pakuri object’s combat power (CP).
    @property
    def cp(self):
        return

    # hp (read-only)
    # Calculates and returns the Pakuri object’s health points (HP).
    @property
    def hp(self):
        return

    # level (read-write)
    # Gets, or sets, the Pakuri object’s level attribute.
    @property
    def level(self):
        return self.__level

    @level.setter
    def set_level(self, level):
        self.__level = level

