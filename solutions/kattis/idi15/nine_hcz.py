# https://open.kattis.com/problems/nine

n = int(input())

for i in range(n):
    d = int(input()) - 1
    pow9 = 9
    result = 8

    while d:
        result *= pow9 ** (d & 1)
        result %= 1000000007
        pow9 *= pow9
        pow9 %= 1000000007
        d >>= 1

    print(result)
