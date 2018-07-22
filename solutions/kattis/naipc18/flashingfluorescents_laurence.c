#include <stdint.h>
#include <stdio.h>

#include "flashingfluorescents_laurence.h"

int main() {
    uint32_t init = 0, n = 0, c;
    while ((c = getchar()) != '\n')
        init |= (c-'0') << n++;

    uint32_t mask = (1 << n) - 1, dst = ~init & mask;

    uint8_t t = T[n][dst / 2];
    if (dst & 1) {
        t &= 0xf;
    } else {
        t >>= 4;
    }

    printf("%d\n", t);
}
