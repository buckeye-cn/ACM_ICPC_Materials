# https://open.kattis.com/problems/bela

n, b = input().split()
n = int(n)
answer = 0

for i in range(n * 4):
    s = input()

    if s[1] == b:
        answer += {'A': 11, 'K': 4, 'Q': 3, 'J': 20, 'T': 10, '9': 14, '8': 0, '7': 0}[s[0]]
    else:
        answer += {'A': 11, 'K': 4, 'Q': 3, 'J': 2, 'T': 10, '9': 0, '8': 0, '7': 0}[s[0]]

print(answer)
