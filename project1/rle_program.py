#---------------------------------------
# PROJECT 1
# =========
# Author: Daniel Li
# Course: COP3504C
# Section: 25452
# Date: Fall 2024
#---------------------------------------

import console_gfx

# Student modules are required to provide all of the following functions with the defined behaviors.
# We recommend completing them in the following order:

# 1. count_runs(flatData: iterable) -> int
#
#   Returns number of runs of data in an image data set;
#   double this result for length of encoded (RLE) byte array.
#
# Ex: count_runs([15, 15, 15, 4, 4, 4, 4, 4, 4]) yields integer 2.

def count_runs(data):
    num_runs = 0
    last_value = None
    for value in data:
        if value != last_value:
            last_value = value
            num_runs += 1
    return num_runs

# 2. to_hex_string(data: iterable) -> str
#
#   Translates data (RLE or raw) a hexadecimal string (without delimiters).
#   This method can also aid debugging.
#
# Ex: to_hex_string([3, 15, 6, 4]) yields string "3f64".

def to_hex_string(data):
    output = ''
    for value in data:
        output += '%02x' % value
    return output

# 3. encode_rle(flat_data: iterable) -> bytes
#
#   Returns encoding (in RLE) of the raw data passed in;
#   used to generate RLE representation of a data.
#
# Ex: encode_rle([15,15,15,4,4,4,4,4,4]) yields b'\x03\x0f\x06\x04' (i.e., [3, 15, 6, 4]).

def encode_rle(data):
    rle = bytes()
    run_value = None
    run_length = 0
    for value in data:
        if value == run_value:
            run_length += 1
        else:
            if run_value != None:
                rle += bytes(run_length, run_value)
            run_value = value
            run_length = 1
    if run_value != None:
        rle += bytes(run_length, run_value)
    return rle

# 4. get_decoded_length(rle_data: iterable) -> int
#
#   Returns decompressed size RLE data;
#   used to generate flat data from RLE encoding.
#   (Counterpart to #2)
#
# Ex: get_decoded_length([3, 15, 6, 4]) yields integer 9.

def get_decoded_length(rle):
    length = 0
    index = 0
    max_index = len(rle) - 2
    while index <= max_index:
        length += rle[index]
        index += 2
    return length

# 5. decode_rle(rle_data: iterable) -> bytes
#
#   Returns the decoded data set from RLE encoded data.
#   This decompresses RLE data for use.
#   (Inverse of #3)
#
# Ex: decode_rle([3, 15, 6, 4]) yields b'\x0f\x0f\x0f\x04\x04\x04\x04\x04\x04'.

def decode_rle(rle):
    data = bytes()
    index = 0
    max_index = len(rle) - 2
    while index <= max_index:
        data += rle[index + 1] * rle[index]
    return data

# 6. string_to_data(data_string: str) -> bytes
#
#   Translates a string in hexadecimal format into byte data (can be raw or RLE).
#   (Inverse of #1)
#
# Ex: string_to_data("3f64") yields b'\x03\x0f\x06\x04' (i.e., [3, 15, 6, 4]).

def string_to_data(s):
    data = bytes()
    index = 0
    max_index = len(s) - 2
    while index <= max_index:
        data += int(s[index, index + 2], 16)
    return data

# 7. to_rle_string(rleData: iterable) -> str
#
#   Translates RLE data into a human-readable representation.
#   For each run, in order, it should display the run length in decimal (1-2 digits);
#   the run value in hexadecimal (1 digit);
#   and a delimiter, ‘:’, between runs.
#   (See examples in standalone section.)
#
# Ex: to_rle_string([10, 15, 6, 4]) yields string "10f:64".

def to_rle_string(rle):
    output = ''
    index = 0
    while index < len(rle):
        if len(output) > 0:
            output += ':'
        output += '%d:%1x' % (rle[index], rle[index + 1])
    return output

# 8. string_to_rle(rleString: str) -> bytes
#
#   Translates a string in human-readable RLE format (with delimiters) into RLE byte data.
#   (Inverse of #7)
#
# Ex: string_to_rle("10f:64") yields b'\x0a\x0f\x06\x04' (i.e., [10, 15, 6, 4]).

def string_to_rle(s):
    # TODO

#---------------------------------------
# When run as the program driver via the main() method, the program should:
#     1) Display welcome message
#     2) Display color test (console_gfx.TEST_RAINBOW)
#     3) Display the menu
#     4) Prompt for input
#---------------------------------------
def main():
    # current image data
    current_data = None

    print("Welcome to the RLE image encoder!")
    print()
    print("Displaying Spectrum Image: ") # space here for some reason
    console_gfx.display_image(console_gfx.TEST_RAINBOW)
    print()

    while True:

        # display the menu
        print("""\

RLE Menu
--------
0. Exit
1. Load File
2. Load Test Image
3. Read RLE String
4. Read RLE Hex String
5. Read Data Hex String
6. Display Image
7. Display RLE String
8. Display Hex RLE Data
9. Display Hex Flat Data
""")

        # query the user for a menu option
        option = input("Select a Menu Option: ")

        match option:
            # Exit
            case '0':
                break

            # Load File
            # "Accepts a filename from the user and invokes console_gfx.load_file(filename: str)."
            case '1':
                filename = input("Enter name of file to load: ")
                current_data = console_gfx.load_file(filename)

            # Load Test Image
            # "Loads console_gfx.TEST_IMAGE."
            case '2':
                current_data = console_gfx.TEST_IMAGE
                print("Test image data loaded.")

            # Read RLE String
            # "Reads RLE data from the user in decimal notation with delimiters."
            case '3':
                rle_string = input("Enter an RLE string to be decoded: ")
                # TODO

            # Read RLE Hex String
            # "Reads RLE data from the user in hexadecimal notation _without_ delimiters."
            case '4':
                rle_hex = input("Enter the hex string holding RLE data: ")
                # TODO

            # Read Data Hex String
            # "Reads raw (flat) data from the user in hexadecimal notation."
            case '5':
                flat_hex = input("Enter the hex string holding flat data: ")
                # TODO

            # Display Image
            # "Displays the current image by invoking the console_gfx.display_image(imageData: bytes) method."
            case '6':
                console_gfx.display_image(current_data)
                # TODO

            # Display RLE String
            # "Converts the current data into a human-readable RLE representation (with delimiters)."
            # "Note that each entry is 2-3 characters; the length is always in _decimal_, and the value in _hexadecimal_!"
            case '7':
                # TODO
                pass

            # Display Hex RLE Data
            # "Converts the current data into RLE hexadecimal representation (without delimiters)."
            case '8':
                # TODO
                pass

            # Display Hex Flat Data
            # "Displays the current raw (flat) data in hexadecimal representation (without delimiters)."
            case '9':
                # TODO
                pass

            # invalid input, display error message
            case _:
                print("Error! Invalid input.")

if __name__ == '__main__':
    main()
