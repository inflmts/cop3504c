##############################################################################
## File: Makefile
##
##  ##########################################################################
##    Project 3: Image Processing
##  ##########################################################################
##
##    Author: Daniel Li
##    Course: COP3504C
##    Section: 25452
##    Date: Oct 29 2024
##
##############################################################################

# stupid way to detect Windows
ifdef WINDIR
executable = image-processor.exe
else
executable = image-processor
endif

$(executable): src/main.cpp
	g++ -Wall -fdiagnostics-color=auto -Og -o $@ $^
