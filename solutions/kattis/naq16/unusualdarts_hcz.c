// https://open.kattis.com/problems/unusualdarts

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d\n", &n);

    for (int i = 0; i < n; ++i) {
        double x[7];
        double y[7];

        for (int i = 0; i < 7; ++i) {
            char buf[16];
            fgets(buf, 16, stdin);

            x[i] = (buf[0] - '0') * 1000 + (buf[2] - '0') * 100 + (buf[3] - '0') * 10 + (buf[4] - '0');
            y[i] = (buf[6] - '0') * 1000 + (buf[8] - '0') * 100 + (buf[9] - '0') * 10 + (buf[10] - '0');
            x[i] *= 0.0003535533905932738;
            y[i] *= 0.0003535533905932738;
        }

        char buf[16];
        fgets(buf, 16, stdin);
        int win = (buf[0] - '0') * 100000
            + (buf[2] - '0') * 10000 + (buf[3] - '0') * 1000 + (buf[4] - '0') * 100 + (buf[5] - '0') * 10 + (buf[6] - '0');

        double s_lo = pow((win - 1) * 0.00001, 1. / 3);
        double s_hi = pow((win + 1) * 0.00001, 1. / 3);

        double s2[7][7];
        bool s3[7][7][7];

        for (int i = 0; i < 6; ++i) {
            for (int j = i + 1; j < 7; ++j) {
                double s = x[i] * y[j] - y[i] * x[j];
                s2[i][j] = s;
                s2[j][i] = -s;
            }
        }
        for (int i = 0; i < 5; ++i) {
            for (int j = i + 1; j < 6; ++j) {
                for (int k = j + 1; k < 7; ++k) {
                    double s = s2[i][j] + s2[j][k] + s2[k][i];
                    bool b = s > 0;
                    s3[i][j][k] = s3[j][k][i] = s3[k][i][j] = b;
                    s3[k][j][i] = s3[j][i][k] = s3[i][k][j] = !b;
                }
            }
        }

        #define MAP_i 0
        #define S_i 0
        #define ITER(from, to) \
            int MAP_##to = MAP_##from | 1 << to; \
            if (MAP_##from == MAP_##to) continue; \
            double S_##to = S_##from + s2[from][to];

        #define ISEC(a, b, c, d) \
            ( \
                (s3[a][b][c] ^ s3[a][b][d]) \
                && (s3[c][d][a] ^ s3[c][d][b]) \
            )

        for (int i = 0; i < 1; ++i) {
            for (int j = 1; j < 6; ++j) {
                ITER(i, j)

                for (int k = 1; k < 7; ++k) {
                    ITER(j, k)

                    for (int l = 1; l < 7; ++l) {
                        ITER(k, l)

                        if (ISEC(i, j, k, l)) continue;

                        for (int m = 1; m < 7; ++m) {
                            ITER(l, m)

                            if (ISEC(i, j, l, m)) continue;
                            if (ISEC(j, k, l, m)) continue;

                            for (int n = 1; n < 7; ++n) {
                                ITER(m, n)

                                if (ISEC(i, j, m, n)) continue;
                                if (ISEC(j, k, m, n)) continue;
                                if (ISEC(k, l, m, n)) continue;

                                for (int o = j + 1; o < 7; ++o) {
                                    ITER(n, o)

                                    double s = fabs(S_o + s2[o][i]);

                                    if (s < s_lo) continue;
                                    if (s > s_hi) continue;

                                    if (ISEC(i, j, n, o)) continue;
                                    if (ISEC(j, k, n, o)) continue;
                                    if (ISEC(k, l, n, o)) continue;
                                    if (ISEC(l, m, n, o)) continue;

                                    if (ISEC(j, k, o, i)) continue;
                                    if (ISEC(k, l, o, i)) continue;
                                    if (ISEC(m, n, o, i)) continue;
                                    if (ISEC(l, m, o, i)) continue;

                                    static char buf[] = "? ? ? ? ? ? ?\n";
                                    buf[0] = i + '1';
                                    buf[2] = j + '1';
                                    buf[4] = k + '1';
                                    buf[6] = l + '1';
                                    buf[8] = m + '1';
                                    buf[10] = n + '1';
                                    buf[12] = o + '1';

                                    // puts(buf);
                                    write(1, buf, 14);

                                    goto done;
                                }
                            }
                        }
                    }
                }
            }
        }

        done:;
    }

    return 0;
}
