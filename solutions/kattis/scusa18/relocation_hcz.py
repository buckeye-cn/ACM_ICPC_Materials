# https://open.kattis.com/problems/relocation

n, q = input().split()
n = int(n)
q = int(q)
x = [int(part) for part in input().split()]

for i in range(q):
    cmd, a, b = input().split()
    a = int(a)
    b = int(b)

    if cmd == '1':
        x[a - 1] = b
    else:
        print(abs(x[a - 1] - x[b - 1]))
