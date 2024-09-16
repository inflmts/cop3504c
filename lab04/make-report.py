#!/usr/bin/env python3

from shutil import which
from subprocess import run

run([which('asciidoctor-pdf'), '--theme', 'default-sans', 'report.adoc'], check=True)
