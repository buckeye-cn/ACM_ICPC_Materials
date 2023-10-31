# https://open.kattis.com/problems/isbnconversion

t = int(input())

for i in range(t):
    s = input()
    parts = s.split('-')

    if 'X' in s[:-1] or len(s) - s.count('-') != 10 or '' in parts or len(parts) > 4 or len(parts) == 4 and len(parts[3]) != 1 or sum(
        (10 - j) * '0123456789X'.find(c)
        for j, c in enumerate(''.join(parts))
    ) % 11 != 0:
        print('invalid')
    else:
        for j in range(10):
            ss = f'978-{s[:-1]}{j}'
            parts = ss.split('-')

            if sum(
                (1 + j % 2 * 2) * '0123456789'.find(c)
                for j, c in enumerate(''.join(parts))
            ) % 10 == 0:
                print(ss)
