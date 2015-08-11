import os
import sys
import re
import inspect
from subprocess import call

requirements = """
This script needs 2 command line arguments:
1) name of Messenger command
2) new value

Example using this script:
python py/change_parameter.py /diamond/source/lambda 4.3
"""

def change_parameter(command, value):
    # get location of this file
    current_path = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
    
    mac_file_name = os.path.join(current_path, "../run.mac")
    mac_temp_file_name = "%s.temp" % mac_file_name
    
    # copy file before editing
    call(['cp', mac_file_name, mac_temp_file_name])
    
    # read content of the file  
    with open(mac_file_name, 'r') as mac_file:
        content = mac_file.read()
    
    # modify content
    pattern = "(?<!#)%s.*\n" % command
    subs = "%s %s\n" % (command, value)
    content = re.sub(pattern, subs, content)
    
    # write modificactions to temporary file
    with open(mac_temp_file_name, 'w') as tmp_file:
        tmp_file.write(content)
    
    # replace the file with rewritten content
    call(['rm', mac_file_name])
    call(['mv', mac_temp_file_name, mac_file_name])
    
    
if __name__ == "__main__":
    change_parameter(sys.argv[1], sys.argv[2])
    
    
    