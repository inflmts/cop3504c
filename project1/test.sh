#!/bin/sh

diff=

for opt; do
  case $opt in
    --diff) diff=1 ;;
    *) echo >&2 "invalid option: $opt"; exit 1 ;;
  esac
done

if [ "$diff" ]; then
  RLE_ECHO_INPUT=1 RLE_FAKE_SPECTRUM=1 python3 rle_program.py < test-input.txt \
    | git diff --no-index --ignore-cr-at-eol --exit-code - test-output.txt
else
  RLE_ECHO_INPUT=1 python3 rle_program.py < test-input.txt
fi
