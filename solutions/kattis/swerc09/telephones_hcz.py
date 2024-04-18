# https://open.kattis.com/problems/telephones

while True:
    n, m = input().split()
    n = int(n)
    m = int(m)

    if not n:
        break

    calls = []

    for i in range(n):
        s, d = input().split()[2:]
        s = int(s)
        d = int(d)
        calls.append((s, d))

    for i in range(m):
        s, d = input().split()
        s = int(s)
        d = int(d)
        print(sum(
            s < ss + dd and ss < s + d
            for ss, dd in calls
        ))
