# https://open.kattis.com/problems/horror

n, h, l = input().split()
n = int(n)
h = int(h)
l = int(l)
x = {int(i) for i in input().split()}
ab = []

for i in range(l):
    ab.append((int(i) for i in input().split()))

hi = [
    (
        0
        if i in x
        else 10000
    )
    for i in range(n)
]

for i in range(n):
    ab = [
        (a, b)
        for a, b in ab
        if hi[a] > i or hi[b] > i
    ]

    for a, b in ab:
        hi[a] = min(hi[a], hi[b] + 1)
        hi[b] = min(hi[b], hi[a] + 1)

print(sorted(
    (-hi[i], i)
    for i in range(n)
)[0][1])
