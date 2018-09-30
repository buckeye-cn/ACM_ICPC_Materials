import sys

for line in sys.stdin:
    if line.lower().find("problem") >= 0:
        print("yes")
    else:
        print("no")
