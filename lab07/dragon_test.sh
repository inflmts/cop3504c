#!/bin/bash
#Test your cowsay program.

OUTPUTFILE="output.txt"
EXECUTABLE="./cowsay"

print_and_run()
{
  COMMAND=$1
  echo ">$COMMAND"
  $COMMAND
}

print_and_run "$EXECUTABLE" > $OUTPUTFILE
print_and_run "$EXECUTABLE Hello World!" >> $OUTPUTFILE
print_and_run "$EXECUTABLE -n kitteh Moew-Moew!" >> $OUTPUTFILE
print_and_run "$EXECUTABLE -l" >> $OUTPUTFILE
print_and_run "$EXECUTABLE -n ninja Hello world!" >> $OUTPUTFILE
print_and_run "$EXECUTABLE -n dragon Fiery RAWR" >> $OUTPUTFILE
print_and_run "$EXECUTABLE -n ice-dragon Ice-cold RAWR" >> $OUTPUTFILE

less $OUTPUTFILE
