import sys
import shutil

inputFile = sys.argv[1]
outputName = sys.argv[2]
startIdx = sys.argv[3]
stopIdx = sys.argv[4]

for i in range(int(startIdx), int(stopIdx) + 1):
    shutil.copy(inputFile, outputName + str(i) + '.mtl')
