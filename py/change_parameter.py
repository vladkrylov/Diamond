#!/usr/bin/python
import os
import sys
import re
import inspect
from subprocess import call

# get location of this file
current_path = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))

mac_file_name = os.path.join(current_path, "/../run.mac")
mac_temp_file_name = "%s.temp" % mac_file_name

# copy file before editing
call(['cp', mac_file_name, mac_temp_file_name])

# read content of the file  
with open(mac_file_name, 'r') as mac_file:
    content = mac_file.read()

# modify content
pattern = "(?<!#)%s.*\n" % sys.argv[1]
subs = "%s %s\n" % (sys.argv[1], sys.argv[2])
content = re.sub(pattern, subs, content)

# write modificactions to temporary file
with open(mac_temp_file_name, 'w') as tmp_file:
    tmp_file.write(content)

# replace the file with rewritten content
call(['rm', mac_file_name])
call(['mv', mac_temp_file_name, mac_file_name])