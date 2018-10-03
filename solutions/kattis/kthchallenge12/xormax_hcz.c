// https://open.kattis.com/problems/xormax

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

char buf[2000000];
long data[60];

int main() {
    fgets(buf, sizeof(buf), stdin);
    fgets(buf, sizeof(buf), stdin);

    long value = 0;

    for (char *i = buf; true; ++i) {
        if (*i >= '0') {
            value *= 10;
            value += *i - '0';
        } else {
            for (int j = 59; j >= 0; --j) {
                if (value >> j) {
                    if (data[j]) {
                        value ^= data[j];
                    } else {
                        data[j] = value;
                        break;
                    }
                }
            }

            value = 0;

            if (*i == '\n') {
                break;
            }
        }
    }

    long result = 0;

    for (int i = 59; i >= 0; --i) {
        if (result < (result ^ data[i])) {
            result = result ^ data[i];
        }
    }

    printf("%ld\n", result);

    return 0;
}
