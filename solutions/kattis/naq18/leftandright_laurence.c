#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    getchar();

    int I = -1;
    for (int i = 0; i < N; i++) {
        if (getchar() != 'L') {
            for (int j = i; j > I; j--)
                printf("%d\n", j+1);
            I = i;
        }
    }
}
