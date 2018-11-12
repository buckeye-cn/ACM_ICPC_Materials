// https://open.kattis.com/problems/carvet

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int data[250][250];

bool visited[250][250];
int route_i[62500];
int route_j[62500];
int tot;

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &data[i][j]);
        }
    }

    int r, c;
    scanf("%d%d", &r, &c);

    r -= 1;
    c -= 1;

    while (data[r][c] >= 0 && !visited[r][c]) {
        route_i[tot] = r;
        route_j[tot] = c;
        tot += 1;

        if (r >= 2 && data[r - 1][c] == data[r][c]) {
            r -= 2;
        } else if (r < m - 2 && data[r + 1][c] == data[r][c]) {
            r += 2;
        } else if (c >= 2 && data[r][c - 1] == data[r][c]) {
            c -= 2;
        } else if (c < n - 2 && data[r][c + 1] == data[r][c]) {
            c += 2;
        } else {
            break;
        }
    }

    if (data[r][c] == -1) {
        for (int i = tot - 1; i > 0; --i) {
            printf("%d ", data[route_i[i]][route_j[i]]);
            tot -= 1;
        }

        printf("%d\n", data[route_i[0]][route_j[0]]);
    } else {
        printf("impossible\n");
    }

    return 0;
}
