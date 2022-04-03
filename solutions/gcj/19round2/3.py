import fractions

t = int(input())

for n_case in range(1, t + 1):
    print('Case #' + str(n_case) + ': ', end='')

    n = int(input())
    c = []
    j = []

    for i in range(n):
        cc, jj = input().split(' ')
        c.append(int(cc))
        j.append(int(jj))

    fmin = fractions.Fraction(1, int(2e9))
    fmax = fractions.Fraction(int(2e9), 1)

    for i in range(1, n):
        c1 = c[i - 1]
        j1 = j[i - 1]
        c2 = c[i]
        j2 = j[i]

        if c1 >= c2 and j1 >= j2:
            fmin = fmax
            break
        if c1 <= c2 and j1 <= j2:
            continue
        if j1 < j2:
            fmin = max(fmin, fractions.Fraction(c1 - c2, j2 - j1))
        else:
            fmax = min(fmax, fractions.Fraction(c1 - c2, j2 - j1))

    if fmin >= fmax:
        print("IMPOSSIBLE")
    else:
        l = 1
        r = int(2e9)
        fmid = (fmin + fmax) / 2

        while l < r:
            m = (l + r) // 2
            f = fmid.limit_denominator(m)

            if f > fmin and f < fmax:
                r = m
            else:
                l = m + 1

        print(l, (l * fmin.numerator) // fmin.denominator + 1)
