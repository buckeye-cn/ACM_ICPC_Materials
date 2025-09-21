# https://open.kattis.com/problems/midjan

input()
x = set(input().split())
y = set(input().split())
print(' '.join(x - y))
print(' '.join(y - x))
