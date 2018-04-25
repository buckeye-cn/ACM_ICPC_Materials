// https://open.kattis.com/problems/piglatin

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int main() {
    char yay[5] = "yay ";
    char buf[4096];

    while (fgets(buf, 4096, stdin)) {
        for (int i = 0; buf[i]; ++i) {
            int i1 = i;
            for (; true; ++i) {
                switch (buf[i]) {
                    case '\n':
                    case ' ':
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                    case 'y':
                        goto out1;
                }
            }
            out1:;

            int i2 = i;
            for (; true; ++i) {
                switch (buf[i]) {
                    case '\n':
                    case ' ':
                        goto out2;
                }
            }
            out2:;

            yay[3] = buf[i];

            fwrite(buf + i2, 1, i - i2, stdout);
            if (i1 == i2) {
                fwrite(yay, 1, 4, stdout);
            } else {
                fwrite(buf + i1, 1, i2 - i1, stdout);
                fwrite(yay + 1, 1, 3, stdout);
            }
        }
    }
}
