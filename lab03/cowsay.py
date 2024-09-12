#!/usr/bin/env python3
########################################
# File: cowsay.py
#
#   This is the main entry point of my primordial cowsay program.
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
#   "On my honor, I have neither given nor received unauthorized aid
#   in doing this assignment."
#
########################################

import sys
from heifer_generator import get_cows

# list_cows(cows: list[Cow])
#
#   Print a list of cows to stdout.
#
def list_cows(cows):
    names = ' '.join(cow.get_name() for cow in cows)
    print(f'Cows available: {names}')

# find_cow(cows: list[Cow], name: str) -> Cow
#
#   Find a cow by name. Returns None if no cow was found
#   with the specified name.
#
def find_cow(cows, name):
    for cow in cows:
        if cow.get_name() == name:
            return cow
    return None

def main():
    args = sys.argv[1:]
    name = 'heifer'

    # this option parser is extremely primitive
    # and only capable of processing the exact test specifications
    if len(args) >= 3 and args[0] == '-n':
        # cowsay -n NAME MESSAGE...
        name = args[1]
        message = ' '.join(args[2:])
    elif len(args) == 1 and args[0] == '-l':
        # cowsay -l
        cows = get_cows()
        list_cows(cows)
        return
    else:
        # cowsay MESSAGE...
        message = ' '.join(args)

    cows = get_cows()
    cow = find_cow(cows, name)
    if cow is None:
        print(f'Could not find {name} cow!')
    else:
        print(message)
        print(cow.get_image())

if __name__ == '__main__':
    main()
