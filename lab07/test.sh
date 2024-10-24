#!/bin/sh
# Test your cowsay program.

sample_file=sample-output.txt

sed 's/^%%%//;t;d' "$sample_file" \
  | while IFS= read -r args; do
      printf '%s\n' "%%%$args"
      eval "build/cowsay $args"
    done \
  | git diff --no-index --ignore-cr-at-eol - "$sample_file"
