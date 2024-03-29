# https://open.kattis.com/problems/speedlimit

while True:
    n = int(input())

    if n < 0:
        break

    l = 0
    now = 0

    for i in range(n):
        s, t = input().split()
        s = int(s)
        t = int(t)

        l += (t - now) * s
        now = t

    print(str(l) + ' miles')
