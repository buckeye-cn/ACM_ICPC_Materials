# https://open.kattis.com/problems/sumoftheothers

import sys

for line in sys.stdin:
    print(sum(
        int(item)
        for item in line.strip().split(' ')
    ) // 2)
