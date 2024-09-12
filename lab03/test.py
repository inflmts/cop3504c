#!/usr/bin/env python

import os
import subprocess
import sys

def print_and_run(*args):
    print(f'\033[1mcowsay {[*args]}\033[0m')
    subprocess.run([sys.executable, 'cowsay.py', *args])

print_and_run('Hello', 'World!')
print_and_run('-n', 'kitteh', 'Hello', 'World!')
print_and_run('-l')
print_and_run('-n', 'ninja', 'Hello', 'world!')
print_and_run('Hello', '-n', 'kitteh')
