# COP3504C

Daniel Li &mdash; <https://inflmts.com>

This is my code for the Advanced Programming Fundamentals (COP3504C) course at
the University of Florida, taken during the Fall 2024 semester. The course uses
Python and C++. All solution code in this repository is my own work, obviously,
because otherwise I wouldn't be publishing here.

Each lab or project directory contains a `README.pdf` file with instructions for
the lab/project. For some labs/projects, sample output is also provided in a
file called `sample-output.txt` or something. These instructions and any
provided modules/auxiliary files are copied verbatim from the source.

The recommended software for the course includes PyCharm and CLion, however
plain Neovim and Windows Terminal work fine for me.

Most of the Python code was developed with Python 3.12, although it should
probably work for older versions. I didn't try to do anything fancy. It will
definitely work on other platforms.

For C++, I use Meson and Ninja as the build system and MinGW as the compiler. I
would very much like to get dirty in a Linux box, but I'm stuck on a Windows
laptop right now and the Ubuntu CISE servers are behind a SSH firewall that lags
sometimes and requires me to have an internet connection at all times.
Especially for the later projects/labs, don't expect it to work outside Windows
(although making it work should just be a matter of cranking the build system
hard enough).
