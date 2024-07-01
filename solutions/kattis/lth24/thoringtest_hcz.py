# https://open.kattis.com/problems/thoringtest

n = int(input())
words = {
    input().strip().lower()
    for i in range(n)
}

for word in input().split():
    if not word.lower() in words:
        print('Thore has left the chat')
        break
else:
    print('Hi, how do I look today?')
