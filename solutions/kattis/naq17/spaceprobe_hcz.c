// https://open.kattis.com/problems/spaceprobe

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int n, k;
long t1, t2;
long offset[10000];
long b[10000];
long e[10000];

long l, r;
int shift;
#define LIMIT 150000000
char slots[LIMIT];

int main() {
    scanf("%d%d%ld%ld", &n, &k, &t1, &t2);

    for (int i = 0; i < n; ++i) {
        scanf("%ld", &offset[i]);
    }

    for (int i = 0; i < k; ++i) {
        scanf("%ld%ld", &b[i], &e[i]);
    }

    l = b[0] - offset[n - 1] > t1 ? b[0] - offset[n - 1] : t1;
    r = e[k - 1] - offset[0] < t2 ? e[k - 1] - offset[0] : t2;
    for (shift = 0; r - l >= LIMIT; ++shift) {
        r >>= 1;
        l >>= 1;
    }

    t1 >>= shift;
    t2 >>= shift;

    for (int i = 0; i < n; ++i) {
        offset[i] >>= shift;
    }

    for (int i = 0; i < k; ++i) {
        b[i] >>= shift;
        e[i] >>= shift;

        b[i] -= l;
        e[i] -= l;
    }

    int lock = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            long bv = b[j] - offset[i];
            long ev = e[j] - offset[i];

            if (bv >= 0 && bv < LIMIT && slots[bv] == 127) continue;
            if (ev >= 0 && ev < LIMIT && slots[ev] == -128) continue;

            if (bv < 0) {
                lock += 1;
            } else if (bv < LIMIT) {
                slots[bv] += 1;
            }

            if (ev < 0) {
                lock -= 1;
            } else if (ev < LIMIT) {
                slots[ev] -= 1;
            }
        }
    }

    long tot = t2 - t1;

    for (int i = 0; i < r - l; ++i) {
        lock += slots[i];

        if (lock) {
            tot -= 1;
        }
    }

    printf("%.10f\n", (double) tot / (t2 - t1));

    return 0;
}
