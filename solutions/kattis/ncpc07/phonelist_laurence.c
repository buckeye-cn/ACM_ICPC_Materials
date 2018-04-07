#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint32_t sn[10];
    uint8_t leaf, has_child;
} Node;

Node nodes[80001];

void test_case() {
    memset(nodes, 0, sizeof(nodes));

    uint16_t N, i = 0;

    scanf("%hu", &N);
    getchar();

    uint32_t node_count = 1;
    for (; i < N; i++) {
        uint32_t ni = 0;
        uint8_t c;
        while (c = getchar(), c != '\n') {
            c -= '0';
            if (nodes[ni].leaf) {
                while (c = getchar(), c != '\n') {}
                goto SKIP;
            }
            if (!nodes[ni].sn[c]) {
                nodes[ni].sn[c] = node_count++;
                nodes[ni].has_child = 1;
            }
            ni = nodes[ni].sn[c];
        }
        if (nodes[ni].has_child) {
            goto SKIP;
        }
        nodes[ni].leaf = 1;
    }

    puts("YES");
    return;

SKIP:;
    for (i += 1; i < N; i++) {
        uint8_t c;
        while (c = getchar(), c != '\n') {}
    }

    puts("NO");
    return;
}

int main() {
    uint16_t N;
    scanf("%hu", &N);
    getchar();

    for (uint16_t i = 0; i < N; i++) {
        test_case();
    }
}
