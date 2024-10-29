#
# Project 3: Image Processing
#

# stupid way to detect Windows
ifdef WINDIR
executable = image-processor.exe
else
executable = image-processor
endif

$(executable): src/main.cpp
	g++ -Wall -fdiagnostics-color=auto -Og -o $@ $^
