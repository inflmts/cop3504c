#!/usr/bin/env python3
########################################
# LAB 02 "Find Four"
#---------------------------------------
# Author: Daniel Li
# Course: COP3504C
# Section: 25452 (Tavassoli)
# Date: Sep 05 2024
########################################

import os
import sys

def env_is_set(name):
    return name in os.environ and len(os.environ[name]) > 0

if env_is_set('FINDFOUR_ECHO_INPUT'):
    orig_input = input
    def input(prompt):
        value = orig_input(prompt)
        print(value)
        return value

#---------------------------------------
# Required Functions
#---------------------------------------

# get_initial_board(rows: int, columns: int) -> list[list[str]]
#
#   Returns a list of size rows, where each entry is itself a list of size columns,
#   where each entry contains the value '.'.
#
def get_initial_board(rows, columns):
    return [['.' for _ in range(columns)] for _ in range(rows)]

# print_board(board: list[list[str]])
#
#   Prints a copy of the board, where board is a list of list objects,
#   each entry a one-character str object.
#
def print_board(board):
    rows = len(board)
    columns = len(board[0])
    print(' _' + '__' * (columns - 1))
    for row in range(rows - 1, -1, -1):
        print('|' + (' ').join(board[row]) + '|')
    print(' -' + '--' * (columns - 1))

# insert_chip(board: list[list[str]], column: int, chip: str) -> int
#
#   Places a chip in the column of the board of the chip type.
#   This method should find the next available spot in that column,
#   if any. This method returns the row in which the chip settles.
#
def insert_chip(board, column, chip):
    rows = len(board)
    for row in range(rows):
        if board[row][column] == '.':
            board[row][column] = chip
            return row
    return -1

# is_win_state(chip: str, board: list[list[str]], row: int, column: int) -> bool
#
#   This method checks if the player represented by specified chip type
#   has won the game by looking on the board at the position (row, column).
#   If this is a win for the player, returns True; otherwise, returns False.
#
def is_win_state(chip, board, row, column):
    rows = len(board)
    columns = len(board[0])

    # check left
    n = 1
    c = column - 1
    while c >= 0:
        if board[row][c] != chip: break
        n += 1
        if n == 4: return True
        c -= 1

    # check right
    c = column + 1
    while c < columns:
        if board[row][c] != chip: break
        n += 1
        if n == 4: return True
        c += 1

    # check down
    n = 1
    r = row - 1
    while r >= 0:
        if board[r][column] != chip: break
        n += 1
        if n == 4: return True
        r -= 1

    # check up
    r = row + 1
    while r < rows:
        if board[r][column] != chip: break
        n += 1
        if n == 4: return True
        r += 1

    ## check down-left
    #n = 1
    #r = row - 1
    #c = column - 1
    #while r >= 0 and c >= 0:
    #    if board[r][c] != chip: break
    #    n += 1
    #    if n == 4: return True
    #    r -= 1
    #    c -= 1

    ## check up-right
    #r = row + 1
    #c = column + 1
    #while r < rows and c < columns:
    #    if board[r][c] != chip: break
    #    n += 1
    #    if n == 4: return True
    #    r += 1
    #    c += 1

    ## check up-left
    #n = 1
    #r = row - 1
    #c = column + 1
    #while r >= 0 and c < columns:
    #    if board[r][c] != chip: break
    #    n += 1
    #    if n == 4: return True
    #    r -= 1
    #    c += 1

    ## check down-right
    #r = row + 1
    #c = column - 1
    #while r < rows and c >= 0:
    #    if board[r][c] != chip: break
    #    n += 1
    #    if n == 4: return True
    #    r += 1
    #    c -= 1

    # nope
    return False

# is_column_full(board: list[list[str]], column: int) -> bool
#
#   This method checks if the column is full.
#   If it is full, returns True; otherwise, returns False.
#   This is not a required function.
#
def is_column_full(board, column):
    return board[-1][column] != '.'

# is_board_full(board: list[list[str]]) -> bool
#
#   This method checks if the board is full.
#   If it is full, returns True; otherwise, returns False.
#
def is_board_full(board):
    columns = len(board[0])
    for column in range(columns):
        if not is_column_full(board, column):
            return False
    return True

#---------------------------------------
# Main Function
#---------------------------------------

def main():
    print('Welcome to Find Four!')
    print('---------------------')

    num_players = 2
    chips = [None, 'x', 'o']

    # query user for height
    while True:
        s = input('Enter height of board (rows): ')
        try:
            rows = int(s)
        except ValueError:
            print('Error: not a number!')
            continue
        if rows < 4:
            print('Error: height must be at least 4!')
            continue
        if rows > 25:
            print('Error: height can be at most 25!')
            continue
        break

    # query user for width
    while True:
        s = input('Enter width of board (columns): ')
        try:
            columns = int(s)
        except ValueError:
            print('Error: not a number!')
            continue
        if columns < 4:
            print('Error: width must be at least 4!')
            continue
        if columns > 25:
            print('Error: width can be at most 25!')
            continue
        break

    # create board
    board = get_initial_board(rows, columns)
    print_board(board)
    print()

    # print chip symbols
    for n in range(1, num_players + 1):
        print(f'Player {n}: {chips[n]}')

    # number of current player, in range [1, num_players]
    current_player = 1

    # main loop
    while True:
        chip = chips[current_player]

        # query player for column
        while True:
            s = input(f'Player {current_player} - Select a Column: ')
            try:
                column = int(s)
            except ValueError:
                print('Error: not a number!')
                continue
            if column < 0 or column >= columns:
                print('Error: no such column!')
                continue
            if is_column_full(board, column):
                print('Error: column is full!')
                continue
            break

        row = insert_chip(board, column, chip)
        assert row != -1
        print_board(board)
        print()

        # check for tie
        if is_board_full(board):
            print('Draw game! Players tied.')
            break

        # check for win
        if is_win_state(chip, board, row, column):
            print(f'Player {current_player} won the game!')
            break

        # change to next player
        current_player = 1 if current_player == num_players else current_player + 1

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        # silence KeyboardInterrupt
        sys.exit(130)
