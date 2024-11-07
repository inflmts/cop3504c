#!/bin/sh

set -u
executable=build/cowsay

sed 's|^>\./cowsay||;t;d' sample-output.txt \
  | while IFS= read -r args; do
      printf '>./cowsay%s\n' "$args"
      eval "\${executable}$args"
    done \
  | git diff --no-index --ignore-cr-at-eol - sample-output.txt
