#!/usr/bin/python3

import os
import sys
from datetime import datetime

startTime = datetime.now()

os.system(". ./build.sh")

print("Time building " + str(datetime.now() - startTime))
