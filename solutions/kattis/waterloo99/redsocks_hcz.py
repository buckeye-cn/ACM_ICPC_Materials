# https://open.kattis.com/problems/redsocks

xm1 = {
    i * (i - 1): i
    for i in range(2, 50001)
}

while True:
    p, q = input().split()
    p = int(p)
    q = int(q)

    if not q:
        break
    if not p:
        print('0 2')
        continue
    if p == q:
        print('2 0')
        continue

    for i in xm1.keys():
        if p * i % q == 0:
            m = p * i // q

            if m in xm1:
                print(xm1[p * i // q], xm1[p * i // p] - xm1[p * i // q])
                break
    else:
        print('impossible')
