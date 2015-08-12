import os
import sys
import re
import inspect
import shutil
from subprocess import call
from change_parameter import change_parameter
from drange import drange

# get location of this file
current_path = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))

out_dir = os.path.join(current_path, '../lambda_scan')

shutil.rmtree(out_dir, ignore_errors=True)
os.mkdir(out_dir)

change_parameter('/run/beamOn', int(1e6))
for poisson_lambda in drange(3, 7.5, 0.5):
    change_parameter('/diamond/source/lambda', str(poisson_lambda))
     
    call(['../bin/Linux-g++/diamond', 'run.mac'])
    shutil.copy('results_nt_DD.csv', os.path.join(out_dir, "lambda=%s.csv" % str(poisson_lambda)))
    