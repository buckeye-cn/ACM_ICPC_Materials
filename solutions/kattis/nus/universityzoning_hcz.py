# https://open.kattis.com/problems/universityzoning

f, s, g = input().split()[2:]
f = int(f)
s = int(s)
g = int(g)

cell = [
    []
    for i in range(f)
]
student = [
    []
    for i in range(f)
]

for i in range(f):
    rc = input().split()[1:]

    for j in range(0, len(rc), 2):
        cell[i].append((int(rc[j]), int(rc[j + 1])))

for i in range(s):
    rr, cc, dd, ff = input().split()
    rr = int(rr)
    cc = int(cc)
    dd = int(dd)
    ff = int(ff) - 1

    student[ff].append((dd, rr, cc))

t = [int(i) for i in input().split()]

print(
    sum(sorted(
        sum(sorted(
            abs(rr - r) + abs(cc - c)
            for (r, c), (dd, rr, cc) in zip(
                sorted(cell[i])[:len(student[i])],
                sorted(student[i])
            )
        )[:t[i]])
        for i in range(f)
    )[:g])
)
