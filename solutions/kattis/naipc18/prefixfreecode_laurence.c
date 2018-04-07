#include <stdint.h>
#include <stdio.h>

const uint32_t MM = 1e9 + 7;

uint32_t ptable[1000001];

typedef struct {
    uint32_t sn[26];
    uint32_t bitset;
    uint32_t order;
} Node;

Node nodes[1000001];

uint32_t counts[20][1000001];

void scan(uint32_t ni);

void scan_sub(uint32_t ni) {
    uint32_t bitset = nodes[ni].bitset;
    do {
        uint8_t n = __builtin_ctz(bitset);
        bitset ^= 1 << n;
        scan(nodes[ni].sn[n]);
    } while (bitset != 0);
}

void scan(uint32_t ni) {
    static uint32_t order_count = 1;
    if (nodes[ni].order != 0) {
        nodes[ni].order = order_count++;
    }
    if (nodes[ni].bitset != 0) {
        scan_sub(ni);
    }
}

int main() {
    uint32_t N, K;

    scanf("%u %u", &N, &K);
    getchar();

    uint32_t node_count = 1;
    for (uint32_t i = 0; i < N; i++) {
        uint32_t ni = 0;
        uint8_t c;
        while (c = getchar(), c != '\n') {
            c -= 'a';
            if (nodes[ni].sn[c] == 0) {
                nodes[ni].sn[c] = node_count++;
                nodes[ni].bitset |= 1 << c;
            }
            ni = nodes[ni].sn[c];
        }
        nodes[ni].order = -1;
    }

    scan_sub(0);

    ptable[K - 1] = 1;
    for (int64_t i = (int64_t)K - 2; i >= 0; i--) {
        ptable[i] = ((uint64_t)ptable[i + 1] * (uint64_t)(N - 1 - i)) % MM;
    }

    uint32_t r = 1;

    uint32_t ni  = 0;
    uint32_t col = 0;
    uint8_t c;
    while (c = getchar() - 'a', col < K) {
        ni = nodes[ni].sn[c];
        if (nodes[ni].order != 0) {
            const uint32_t ord = nodes[ni].order - 1;
            uint32_t o = ord;

            for (int32_t i = 19; i >= 0; i--) {
                if ((ord & (1 << i)) > 0)
                    o -= counts[i][(ord >> i) ^ 1];
                counts[i][ord >> i] += 1;
            }

            r += ((uint64_t)o * (uint64_t)ptable[col]) % MM;
            r %= MM;

            ni = 0;
            col += 1;
        }
    }

    printf("%u\n", r);
}
