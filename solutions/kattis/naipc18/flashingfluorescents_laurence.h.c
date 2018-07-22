// used to generate flashingfluorescents_laurence.h

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef uint32_t u32;

uint8_t TIME[17][1<<16];

bool TABLE[17][1<<16];

int main() {
    for (u32 L = 1; L <= 16; L++) {
        u32 MASK = (1 << L) - 1;

        for (u32 t1 = 1; t1 < L+1; t1++) {
            memset(TABLE, 0, sizeof(TABLE));

            TABLE[0][0] = true;

            for (u32 t0 = 1; t0 <= t1; t0++) {
                u32 flip = (1 << (t1 + 1 - t0)) - 1;

                for (u32 st = 0; st < 1<<L; st++) {

                    if (TABLE[t0-1][st]) {

                        for (u32 i = 0; i < L; i++) {
                            u32 st_new = st ^ ((flip<<i) & MASK);
                            TABLE[t0][st_new] = true;

                            if (st_new && !TIME[L][st_new]) {
                                TIME[L][st_new] = t1;
                            }
                        }

                        TABLE[t0][st] = true;
                    }
                }
            }
        }
    }

    //printf("%d\n", TIME[1][1]);

    printf("static char const* const T[17] = { \"\",\n");
    for (u32 L = 1; L <= 16; L++) {
        printf("\"", L);
        for (u32 i = 0; i < 1<<L; i += 2) {
            uint8_t c = (TIME[L][i] << 4) | TIME[L][i+1];
            if (32 <= c && c <= 126 && c != '"' && !('0' <= c && c <= '9')) {
                printf("%c", c);
            } else {
                printf("\\%o", c);
            }
        }
        printf("\",\n");
    }
    printf("};\n");
}
