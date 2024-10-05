########################################
# File: pakudex.py
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

#---------------------------------------
# Entry Point
#---------------------------------------

# When run as a program, the pakudex module should...
#
#   1) Display a welcome message
#   2) Prompt for input & conduct input error checking
#   3) Follow the output and formatting in this document
#   4) Not have print statements in the class method calls
#   5) Only run main() if invoked directly (i.e., check __name__)
#   6) Have no global variables
#

def main():
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
'''
        )

        action = input('What would you like to do? ')
        print()

        match action:
            case '1':
                pass
            case '2':
                pass
            case '3':
                pass
            case '4':
                pass
            case '5':
                pass
            case '6':
                pass
            case '7':
                break
