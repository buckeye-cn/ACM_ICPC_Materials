// https://open.kattis.com/problems/froshweek2

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int task[100000];
int quiet[100000];

int main() {
    int n, m;
    scanf("%d %d\n", &n, &m);

    char buf[7];

    for (int i = 0; i < n; ++i) {
        fread(buf, 1, 7, stdin);
        int t = (buf[1] - '0') * 10000
            + (buf[2] - '0') * 1000
            + (buf[3] - '0') * 100
            + (buf[4] - '0') * 10
            + (buf[5] - '0') * 1;

        task[t] += 1;
    }

    for (int i = 0; i < m; ++i) {
        fread(buf, 1, 7, stdin);
        int l = (buf[1] - '0') * 10000
            + (buf[2] - '0') * 1000
            + (buf[3] - '0') * 100
            + (buf[4] - '0') * 10
            + (buf[5] - '0') * 1;

        quiet[l] += 1;
    }

    int remain = 0;
    int done = 0;

    for (int i = 99999; i >= 0; --i) {
        remain += quiet[i];

        int delta = task[i] < remain ? task[i] : remain;

        done += delta;
        remain -= delta;
    }

    printf("%d\n", done);

    return 0;
}
