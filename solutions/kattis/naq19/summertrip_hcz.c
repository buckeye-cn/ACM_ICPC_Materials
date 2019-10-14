// https://open.kattis.com/problems/summertrip

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

char buf[100001];
int inside[26];

int main() {
    char *p = fgets(buf, 100001, stdin);

    int total = 0;

    while (*p >= 'a') {
        int pos = *p++ - 'a';

        inside[pos] = -1;
        total -= 1;

        total += (inside[0] >> pos) & 1;
        total += (inside[1] >> pos) & 1;
        total += (inside[2] >> pos) & 1;
        total += (inside[3] >> pos) & 1;
        total += (inside[4] >> pos) & 1;
        total += (inside[5] >> pos) & 1;
        total += (inside[6] >> pos) & 1;
        total += (inside[7] >> pos) & 1;
        total += (inside[8] >> pos) & 1;
        total += (inside[9] >> pos) & 1;
        total += (inside[10] >> pos) & 1;
        total += (inside[11] >> pos) & 1;
        total += (inside[12] >> pos) & 1;
        total += (inside[13] >> pos) & 1;
        total += (inside[14] >> pos) & 1;
        total += (inside[15] >> pos) & 1;
        total += (inside[16] >> pos) & 1;
        total += (inside[17] >> pos) & 1;
        total += (inside[18] >> pos) & 1;
        total += (inside[19] >> pos) & 1;
        total += (inside[20] >> pos) & 1;
        total += (inside[21] >> pos) & 1;
        total += (inside[22] >> pos) & 1;
        total += (inside[23] >> pos) & 1;
        total += (inside[24] >> pos) & 1;
        total += (inside[25] >> pos) & 1;

        inside[0] &= ~(1 << pos);
        inside[1] &= ~(1 << pos);
        inside[2] &= ~(1 << pos);
        inside[3] &= ~(1 << pos);
        inside[4] &= ~(1 << pos);
        inside[5] &= ~(1 << pos);
        inside[6] &= ~(1 << pos);
        inside[7] &= ~(1 << pos);
        inside[8] &= ~(1 << pos);
        inside[9] &= ~(1 << pos);
        inside[10] &= ~(1 << pos);
        inside[11] &= ~(1 << pos);
        inside[12] &= ~(1 << pos);
        inside[13] &= ~(1 << pos);
        inside[14] &= ~(1 << pos);
        inside[15] &= ~(1 << pos);
        inside[16] &= ~(1 << pos);
        inside[17] &= ~(1 << pos);
        inside[18] &= ~(1 << pos);
        inside[19] &= ~(1 << pos);
        inside[20] &= ~(1 << pos);
        inside[21] &= ~(1 << pos);
        inside[22] &= ~(1 << pos);
        inside[23] &= ~(1 << pos);
        inside[24] &= ~(1 << pos);
        inside[25] &= ~(1 << pos);
    }

    printf("%d\n", total);

    return 0;
}
