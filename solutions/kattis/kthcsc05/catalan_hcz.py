# https://open.kattis.com/problems/catalan

frac = [1]

for i in range(1, 10001):
    frac.append(frac[-1] * i)

n = int(input())
for i in range(n):
    v = int(input())

    print(frac[2 * v] // frac[v + 1] // frac[v])
