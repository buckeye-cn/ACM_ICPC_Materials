# https://open.kattis.com/problems/dualdivisibility

a, b = input().split()
a = int(a)
b = int(b)

if a % b:
    print(0)
else:
    a //= b
    n = 1

    for i in range(2, 1000000):
        nn = 1

        if a % i == 0:
            while a % i == 0:
                a //= i
                nn += 1

            n *= nn

    print(n)
