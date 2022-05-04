# https://open.kattis.com/problems/fairwarning

import math

t = int(input())

for n_case in range(1, t + 1):
    print('Case #' + str(n_case) + ': ', end='')

    vals = [int(val) for val in input().split(' ')[1:]]

    g = abs(vals[1] - vals[0])

    for val in vals[2:]:
        g = math.gcd(g, abs(val - vals[0]))

    print(-vals[0] % g)
