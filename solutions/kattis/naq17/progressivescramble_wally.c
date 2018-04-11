#include <stdio.h>

int to_num(char ch) {
        if (ch == ' ') {
                return 0;
        } else {
                return ch - 'a' + 1;
        }
}

char to_char(int num) {
        if (num == 0) {
                return ' ';
        } else {
                return num - 1 + 'a';
        }
}

int main(void)
{
        int n;
        scanf("%d", &n);
        getchar();
        for (int i = 0; i < n; ++i) {
                char ch = getchar();
                getchar();
                if (ch == 'e') {
                        int prev = 0;
                        int curr = 0;
                        while ((ch = getchar()) != '\n') {
                                if (ch == ' ') {
                                        curr = 0;
                                } else {
                                        curr = ch - 'a' + 1;
                                }
                                /* printf("%d\n", curr); */

                                curr += prev;
                                prev = curr;
                                curr %= 27;
                                if (curr == 0) {
                                        putchar(' ');
                                } else {
                                        putchar(curr - 1 + 'a');
                                }
                        }
                } else {
                        int prev = 0;
                        int curr = 0;
                        while ((ch = getchar()) != '\n') {
                                curr = to_num(ch);
                                /* curr += 27; */
                                /* curr -= prev; */
                                /* prev = curr; */
                                while (curr - prev < 0) {
                                        curr += 27;
                                }
                                int temp = prev;
                                prev = curr;
                                curr -= temp;
                                putchar(to_char(curr));
                        }
                }
                putchar('\n');
        }
}
