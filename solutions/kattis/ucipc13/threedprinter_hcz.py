# https://open.kattis.com/problems/threedprinter

v_all = 0;
n = int(input())

for i in range(n):
    f = int(input())

    for j in range(f):
        arr = input().split(' ')

        for k in range(int(arr[0])):
            x, y, z = [float(i) for i in arr[3 * k + 1:3 * k + 4]]

            if k:
                xx = (yp - y0) * (z - z0) - (zp - z0) * (y - y0)
                yy = (zp - z0) * (x - x0) - (xp - x0) * (z - z0)
                zz = (xp - x0) * (y - y0) - (yp - y0) * (x - x0)

                v_all += abs(
                    (x0 - x00) * xx
                    + (y0 - y00) * yy
                    + (z0 - z00) * zz
                ) / 6
            else:
                x0, y0, z0 = x, y, z

                if not j:
                    x00, y00, z00 = x, y, z

            xp, yp, zp = x, y, z

print(f'{v_all:.2f}')
