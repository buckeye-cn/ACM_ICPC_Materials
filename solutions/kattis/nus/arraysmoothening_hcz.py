# https://open.kattis.com/problems/arraysmoothening

n, k = input().split()
n = int(n)
k = int(k)

count_map = {None: 0}

for a in input().split():
    count_map[a] = count_map.get(a, 0) + 1

counts = sorted(count_map.values())
m = 1

while True:
    if k <= m * (counts[-1] - counts[-2]):
        print(counts[-1] - k // m)
        break

    k -= m * (counts[-1] - counts[-2])
    counts.pop()
    m += 1
