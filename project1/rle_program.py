#!/usr/bin/env python3
########################################
# File: rle_program.py
#
#   ------------------------------------
#   Project 1: RLE with Images
#   ------------------------------------
#
#   Author: Daniel Li
#   Course: COP3504C
#   Section: 25452 (Tavassoli)
#   Date: Fall 2024
#
#   In this project students will develop routines to encode and decode data
#   for images using run-length encoding (RLE). Students will implement
#   encoding and decoding of raw data, conversion between data and strings, and
#   display of information by creating procedures that can be called from
#   within their programs and externally. This project will give students
#   practice with loops, strings, arrays, methods, and type-casting.
#
########################################

import console_gfx
import os
import sys

_echo_input_enabled = False

# Wraps the input() function to echo input to stdout.
def _enable_echo_input():
    global input, _echo_input_enabled
    if _echo_input_enabled:
        return
    orig_input = input
    def input(*args, **kwargs):
        value = orig_input(*args, **kwargs)
        print(value)
        return value
    _echo_input_enabled = True

########################################
#
#   Module Functions
#   ------------------------------------
#
#   Student modules are required to provide all of the following functions with
#   the defined behaviors. We recommend completing them in the following order:
#
########################################

# 1. count_runs(flatData: iterable) -> int
#
#   Returns number of runs of data in an image data set;
#   double this result for length of encoded (RLE) byte array.
#
#   Ex: count_runs([15, 15, 15, 4, 4, 4, 4, 4, 4]) yields integer 2.
#
def count_runs(data):
    num_runs = 0
    run_value = None
    run_length = 0
    for value in data:
        if value == run_value and run_length < 15:
            run_length += 1
        else:
            run_value = value
            run_length = 1
            num_runs += 1
    return num_runs

# 2. to_hex_string(data: iterable) -> str
#
#   Translates data (RLE or raw) a hexadecimal string (without delimiters).
#   This method can also aid debugging.
#
#   Ex: to_hex_string([3, 15, 6, 4]) yields string "3f64".
#
def to_hex_string(data):
    output = ''
    for value in data:
        output += '%1x' % value
    return output

# 3. encode_rle(flat_data: iterable) -> bytes
#
#   Returns encoding (in RLE) of the raw data passed in;
#   used to generate RLE representation of a data.
#
#   Ex: encode_rle([15,15,15,4,4,4,4,4,4]) yields b'\x03\x0f\x06\x04' (i.e., [3, 15, 6, 4]).
#
def encode_rle(data):
    rle_data = bytes()
    run_value = None
    run_length = 0
    for value in data:
        if value == run_value and run_length < 15:
            run_length += 1
        else:
            if run_value != None:
                rle_data += bytes((run_length, run_value))
            run_value = value
            run_length = 1
    if run_value != None:
        rle_data += bytes((run_length, run_value))
    return rle_data

# 4. get_decoded_length(rle_data: iterable) -> int
#
#   Returns decompressed size RLE data;
#   used to generate flat data from RLE encoding.
#   (Counterpart to #2)
#
#   Ex: get_decoded_length([3, 15, 6, 4]) yields integer 9.
#
def get_decoded_length(rle_data):
    length = 0
    for index in range(0, len(rle_data), 2):
        length += rle_data[index]
    return length

# 5. decode_rle(rle_data: iterable) -> bytes
#
#   Returns the decoded data set from RLE encoded data.
#   This decompresses RLE data for use.
#   (Inverse of #3)
#
#   Ex: decode_rle([3, 15, 6, 4]) yields b'\x0f\x0f\x0f\x04\x04\x04\x04\x04\x04'.
#
def decode_rle(rle_data):
    data = bytes()
    for index in range(0, len(rle_data), 2):
        length = rle_data[index]
        value = rle_data[index + 1]
        for _ in range(length):
            data += bytes((value,))
    return data

# 6. string_to_data(data_string: str) -> bytes
#
#   Translates a string in hexadecimal format into byte data (can be raw or RLE).
#   (Inverse of #1)
#
#   Ex: string_to_data("3f64") yields b'\x03\x0f\x06\x04' (i.e., [3, 15, 6, 4]).
#
def string_to_data(data_str):
    return bytes(int(char, 16) for char in data_str)

# 7. to_rle_string(rleData: iterable) -> str
#
#   Translates RLE data into a human-readable representation.
#   For each run, in order, it should display the run length in decimal (1-2 digits);
#   the run value in hexadecimal (1 digit);
#   and a delimiter, ‘:’, between runs.
#   (See examples in standalone section.)
#
#   Ex: to_rle_string([10, 15, 6, 4]) yields string "10f:64".
#
def to_rle_string(rle_data):
    return ':'.join(
        '%d%1x' % (rle_data[index], rle_data[index + 1])
        for index in range(0, len(rle_data), 2))

# 8. string_to_rle(rleString: str) -> bytes
#
#   Translates a string in human-readable RLE format (with delimiters) into RLE byte data.
#   (Inverse of #7)
#
#   Ex: string_to_rle("10f:64") yields b'\x0a\x0f\x06\x04' (i.e., [10, 15, 6, 4]).
#
def string_to_rle(rle_str):
    rle_data = bytes()
    entries = rle_str.split(':')
    for entry in entries:
        if len(entry) == 0:
            raise ValueError()
        length = int(entry[:-1], 10)
        value = int(entry[-1], 16)
        rle_data += bytes((length, value))
    return rle_data


########################################
#
#   Standalone Mode (Menu)
#   ------------------------------------
#
#   When run as the program driver via the main() method, the program should:
#       1) Display welcome message
#       2) Display color test (console_gfx.TEST_RAINBOW)
#       3) Display the menu
#       4) Prompt for input
#
########################################

class Standalone:
    def __init__(self, fake_spectrum=False):
        # current image data
        self.data = None
        # whether to use fake spectrum image
        self.fake_spectrum = fake_spectrum

    def run(self):
        # print introductory banner
        print('Welcome to the RLE image encoder!')
        print()
        print('Displaying Spectrum Image: ') # space here for some reason
        if self.fake_spectrum:
            print('╔════════════════╗')
            print('║▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀║')
            print('╚════════════════╝')
        else:
            console_gfx.display_image(console_gfx.TEST_RAINBOW)
        print()

        # main loop
        while self.menu():
            pass

    def menu(self):
        # print the menu
        print()
        print('RLE Menu')
        print('--------')
        print('0. Exit')
        print('1. Load File')
        print('2. Load Test Image')
        print('3. Read RLE String')
        print('4. Read RLE Hex String')
        print('5. Read Data Hex String')
        print('6. Display Image')
        print('7. Display RLE String')
        print('8. Display Hex RLE Data')
        print('9. Display Hex Flat Data')
        print()

        # query the user for a menu option
        option = input('Select a Menu Option: ')

        match option:
            case '0': return False
            case '1': self.load_file()
            case '2': self.load_test()
            case '3': self.read_rle_str()
            case '4': self.read_rle_hex()
            case '5': self.read_data_hex()
            case '6': self.display_image()
            case '7': self.display_rle_str()
            case '8': self.display_rle_hex()
            case '9': self.display_data_hex()
            case _: print('Error! Invalid input.')

        return True

    def load_file(self):
        # Accepts a filename from the user and invokes console_gfx.load_file(filename: str):
        #     Select a Menu Option: 1
        #     Enter name of file to load: testfiles/uga.gfx
        filename = input('Enter name of file to load: ')
        self.data = console_gfx.load_file(filename)

    def load_test(self):
        # Loads console_gfx.TEST_IMAGE:
        #     Select a Menu Option: 2
        #     Test image data loaded.
        self.data = console_gfx.TEST_IMAGE
        print('Test image data loaded.')

    def read_rle_str(self):
        # Reads RLE data from the user in decimal notation with delimiters (smiley example):
        #     Select a Menu Option: 3
        #     Enter an RLE string to be decoded: 28:10:6B:10:10B:10:2B:10:12B:10:2B:10:5B:20:11B:10:6B:10
        rle_str = input('Enter an RLE string to be decoded: ')
        rle_data = string_to_rle(rle_str)
        self.data = decode_rle(rle_data)

    def read_rle_hex(self):
        # Reads RLE data from the user in hexadecimal notation without delimiters (smiley example):
        #     Select a Menu Option: 4
        #     Enter the hex string holding RLE data: 28106B10AB102B10CB102B105B20BB106B10
        #     RLE decoded length: 66
        rle_hex = input('Enter the hex string holding RLE data: ')
        rle_data = string_to_data(rle_hex)
        self.data = decode_rle(rle_data)
        print(f'RLE decoded length: {get_decoded_length(rle_data)}')

    def read_data_hex(self):
        # Reads raw (flat) data from the user in hexadecimal notation (smiley example):
        #     Select a Menu Option: 5
        #     Enter the hex string holding flat data: 880bbbbbb0bbbbbbbbbb0bb0bbbbbbbbbbbb0bb0bbbbb00bbbbbbbbbbb0bbbbbb0
        #     Number of runs: 18
        data_hex = input('Enter the hex string holding flat data: ')
        self.data = string_to_data(data_hex)
        print(f'Number of runs: {count_runs(self.data)}')

    def display_image(self):
        # Displays the current image by invoking the console_gfx.display_image(imageData: bytes) method.
        print('Displaying image...')
        if self.data is not None:
            console_gfx.display_image(self.data)
        else:
            print('(no data)')

    def display_rle_str(self):
        # Converts the current data into a human-readable RLE representation (with delimiters):
        #     Select a Menu Option: 7
        #     RLE representation: 28:10:6b:10:10b:10:2b:10:12b:10:2b:10:5b:20:11b:10:6b:10
        # Note that each entry is 2-3 characters; the length is always in decimal, and the value in hexadecimal!
        output = to_rle_string(encode_rle(self.data)) if self.data is not None else '(no data)'
        print(f'RLE representation: {output}')

    def display_rle_hex(self):
        # Converts the current data into RLE hexadecimal representation (without delimiters):
        #     Select a Menu Option: 8
        #     RLE hex values: 28106b10ab102b10cb102b105b20bb106b10
        output = to_hex_string(encode_rle(self.data)) if self.data is not None else '(no data)'
        print(f'RLE hex values: {output}')

    def display_data_hex(self):
        # Displays the current raw (flat) data in hexadecimal representation (without delimiters):
        #     Select a Menu Option: 9
        #     Flat hex values: 880bbbbbb0bbbbbbbbbb0bb0bbbbbbbbbbbb0bb0bbbbb00bbbbbbbbbbb0bbbbbb0
        output = to_hex_string(self.data) if self.data is not None else '(no data)'
        print(f'Flat hex values: {output}')

def main():
    # for testing
    if len(os.getenv('RLE_ECHO_INPUT', '')) > 0:
        _enable_echo_input()
    fake_spectrum = len(os.getenv('RLE_FAKE_SPECTRUM', '')) > 0
    sys.stdout.reconfigure(encoding='utf-8')

    standalone = Standalone(fake_spectrum=fake_spectrum)
    standalone.run()

if __name__ == '__main__':
    main()
