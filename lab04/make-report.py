#!/usr/bin/env python3

import subprocess
import sys

if sys.platform == 'win32':
    executable = 'asciidoctor-pdf.bat'
else:
    executable = 'asciidoctor'

subprocess.run([executable, '--theme', 'default-sans', 'report.adoc'], check=True)
