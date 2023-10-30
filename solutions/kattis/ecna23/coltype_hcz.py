# https://open.kattis.com/problems/coltype

s = input()[::-1]

for i in range(4, 100, 2):
    n = 1 << i

    for c in s:
        if c == 'O':
            if n % 6 != 4:
                n = 0
                break

            n //= 3
        else:
            n *= 2
    else:
        print(n)
        break
else:
    print('INVALID')
