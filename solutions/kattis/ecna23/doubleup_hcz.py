# https://open.kattis.com/problems/doubleup

input()

stk = []

for part in input().split():
    a = int(part)

    while stk and stk[-1] <= a:
        a <<= stk.pop() == a

    stk.append(a)

print(max(stk))
