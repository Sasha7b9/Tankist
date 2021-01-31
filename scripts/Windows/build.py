import os
import sys
from datetime import datetime

if len(sys.argv) < 3:
    print("Too few parameters. Type \"build.py [debug|release] [build|rebuild]")
    quit()
  
startTime = datetime.now()

command = "MSBuild.exe ..\\..\\generated\\" + sys.argv[1] + "\\Engine\\PiEngine2.sln /p:Configuration=" + sys.argv[1] +" /t:" + sys.argv[2] +" -clp:ErrorsOnly;WarningsOnly -nologo /m";
print(command)
os.system(command)
  
print("\nfull time ", datetime.now() - startTime)
