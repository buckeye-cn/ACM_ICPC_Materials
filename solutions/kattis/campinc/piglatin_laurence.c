#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

char buf[12500000];

int main() {
    fread(buf, sizeof(char), 12500000, stdin);

    bool mw = false;
    char *p = buf, *p0, *p1;

    for (;;) {
        char c = *p;
        switch (c) {
            case '\0':
                return 0;
            case ' ': case '\n':
                if (mw) {
                    if (p0 < p1)
                        for (; p0 < p1; p0++)
                            putchar(*p0);
                    else
                        putchar('y');
                    putchar('a');
                    putchar('y');
                }
                mw = false;

                putchar(c);
                p++;
                continue;
        }
        if (!mw)
            p0 = p;
        mw = true;
        switch (c) {
            case 'a': case 'e': case 'i': case 'o': case 'u': case 'y':
                p1 = p;
                do { putchar(*(p++)); } while ('a' <= *p && *p <= 'z');
                continue;
            default:
                p++;
                break;
        }
    }

    return 1;
}
