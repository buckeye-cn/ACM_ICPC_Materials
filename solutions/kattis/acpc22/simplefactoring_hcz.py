# https://open.kattis.com/problems/simplefactoring

n = int(input())

for i in range(n):
    a, b, c = [int(part) for part in input().split()]
    x = b * b - 4 * a * c

    if x >= 0 and int(x ** .5) ** 2 == x:
        print('YES')
    else:
        print('NO')
