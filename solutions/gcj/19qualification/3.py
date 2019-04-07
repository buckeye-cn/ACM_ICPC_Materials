import math

t = int(input())

for n_case in range(1, t + 1):
    print('Case #' + str(n_case) + ': ', end='')

    n, l = (int(i) for i in input().split(' '))
    muls = [int(i) for i in input().split(' ')]
    vals = [0] * (l + 1)

    for i in range(1, l):
        if muls[i - 1] != muls[i]:
            pos = i
            vals[i] = math.gcd(muls[i - 1], muls[i])

    for i in range(pos, 0, -1):
        vals[i - 1] = muls[i - 1] // vals[i]

    for i in range(pos, l):
        vals[i + 1] = muls[i] // vals[i]

    vals_order = list(set(vals))
    vals_order.sort()

    for val in vals:
        print(chr(65 + vals_order.index(val)), end='')

    print()
