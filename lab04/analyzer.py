#!/usr/bin/env python3
########################################
# File: analyzer.py
#
#   ------------------------------------
#   Lab 04: Time Complexity & Profiling
#   ------------------------------------
#
#   Author: Daniel Li
#   Course: COP3504C
#   Section: 25452 (Tavassoli)
#   Date: Sep 12 2024
#
########################################

from time import time

# Students will implement the analyzer module with a main entry point
# and two search methods as follows.

#---------------------------------------
# Search Methods
#---------------------------------------

# linear_search(container: tuple(str), element: str) -> int
#
#   Uses linear search to find specified element in container.
#   Returns index of element, or -1 if not found.
#
def linear_search(container, element):
    for index in range(len(container)):
        if container[index] == element:
            return index
    return -1

# binary_search(container: tuple(str), element: str) -> int
#
#   Uses binary search to find specified element in container.
#   Returns index of element, or -1 if not found.
#
def binary_search(container, element):
    lower = 0
    upper = len(container)
    while lower < upper:
        mid = (lower + upper) // 2
        if element < container[mid]:
            upper = mid
        elif element > container[mid]:
            lower = mid + 1
        else:
            return mid
    return -1

#---------------------------------------
# Other Methods
#---------------------------------------

# This function tests both search methods by searching for
# the specified element in a list.
def profile_search(container, element):
    print(f'Searching for \'{element}\':')

    start_time = time()
    index = linear_search(container, element)
    end_time = time()
    delta_time = end_time - start_time
    print(f'  linear search: found {index} in {delta_time}s')

    start_time = time()
    index = binary_search(container, element)
    end_time = time()
    delta_time = end_time - start_time
    print(f'  binary search: found {index} in {delta_time}s')

#---------------------------------------
# Entry Point (main)
#---------------------------------------

# This module will have a main() function which will execute if the module is
# directly invoked. The main function should complete the following steps,
# documenting results and answer questions in the write-up:
#
#     1) Access the data set from the stringdata module (via the dataset value).
#     2) Search for "not_here" using both algorithms. Capture the time each method requires to execute.
#     3) Search for "mzzzz" using both algorithms. Capture the time each method requires to execute.
#     4) Search for "aaaaa" using both algorithms. Capture the time each method requires to execute.
#
def main():
    import stringdata
    print('Generating dataset...')
    start_time = time()
    dataset = stringdata.get_data()
    end_time = time()
    delta_time = end_time - start_time
    print(f'Generated {len(dataset)} values in {delta_time}s')

    profile_search(dataset, 'not_here')
    profile_search(dataset, 'mzzzz')
    profile_search(dataset, 'aaaaa')

if __name__ == '__main__':
    main()
