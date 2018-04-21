#include <stdint.h>
#include <stdio.h>

const uint16_t click[] = {
    0b110100000,
    0b111010000,
    0b011001000,
    0b100110100,
    0b010111010,
    0b001011001,
    0b000100110,
    0b000010111,
    0b000001011,
};

uint8_t table[512];

void dfs(uint8_t i, uint16_t cells, uint8_t n) {
    table[cells] = (table[cells] && table[cells] < n) ? table[cells] : n;
    if (i < 9) {
        dfs(i + 1, cells, n);
        dfs(i + 1, cells ^ click[i], n + 1);
    }
}

int main() {
    dfs(0, 0, 0);

    uint16_t N;
    scanf("%hu", &N);
    for (uint16_t i = 0; i < N; i++) {
        uint16_t cells = 0;
        getchar();
        if (getchar() == '*') cells ^= 1 << 0;
        if (getchar() == '*') cells ^= 1 << 1;
        if (getchar() == '*') cells ^= 1 << 2;
        getchar();
        if (getchar() == '*') cells ^= 1 << 3;
        if (getchar() == '*') cells ^= 1 << 4;
        if (getchar() == '*') cells ^= 1 << 5;
        getchar();
        if (getchar() == '*') cells ^= 1 << 6;
        if (getchar() == '*') cells ^= 1 << 7;
        if (getchar() == '*') cells ^= 1 << 8;
        printf("%u\n", table[cells]);
    }
}
