# https://open.kattis.com/problems/hardwoodspecies

import sys

count = {}

for line in sys.stdin:
    count[line] = count.get(line, 0) + 1

total = sum(count.values())

for line in sorted(count):
    print(line[:-1], 100 * count[line] / total)
