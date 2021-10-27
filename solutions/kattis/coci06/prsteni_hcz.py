# https://open.kattis.com/problems/prsteni

import math

n = int(input())
r = [
    int(part)
    for part in input().split(' ')
]

x, y = 1, 1

for i in range(1, n):
    x = r[i - 1] * x
    y = r[i] * y
    g = math.gcd(x, y)
    x = x // g
    y = y // g
    print(str(x) + '/' + str(y))
