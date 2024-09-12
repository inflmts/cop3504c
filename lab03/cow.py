########################################
# File: cow.py
#
#   This defines the Cow class,
#   which is used by the heifer_generator and cowsay modules.
#
#   ------------------------------------
#   LAB 03 "The Cow Says..."
#   ------------------------------------
#
#   Author: Daniel Li
#   Course: COP3504C
#   Section: 25452 (Tavassoli)
#   Date: Sep 10 2024
#
########################################

class Cow:

    # __init__(self, name: str)
    #
    #   This method should be the only constructor for this class.
    #   There should not be a default constructor!
    #
    def __init__(self, name):
        self.__name = name
        self.__image = None

    # get_name(self) -> str
    #
    #   Returns the name of the cow.
    #
    def get_name(self):
        return self.__name

    # get_image(self) -> str
    #
    #   Returns the image used to display the cow (after the message).
    #
    def get_image(self):
        return self.__image

    # set_image(self, image: str)
    #
    #   Sets the image used to display the cow (after the message).
    #
    def set_image(self, image):
        self.__image = image
