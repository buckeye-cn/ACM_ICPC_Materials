#include <bits/stdc++.h>

using namespace std;

int board[103][103];
int checked[103][103];
int maxn = 0;
int maxnlen;

void output(int x) {
    int len = x == 0 ? 0 : x < 10 ? 1 : 2;
    switch (maxnlen - len) {
        case 3: cout << '.';
        case 2: cout << '.';
        case 1: cout << '.';
    }
    if (x > 0)
        cout << x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N, M;
    cin >> N >> M;

    cin.get();
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            board[i][j] = cin.get() == 'T' ? 2 : 0;
        }
        cin.get();
    }

#define run(di, dj) \
    if (!board[i + (di)][j + (dj)] && board[i][j]) { \
        checked[i][j] = s; \
        board[i][j]   = 1; \
    } \

    for (int s = 1; s <= 51; s++) {
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                run(0, -1);

        for (int i = 1; i <= N; i++)
            for (int j = M; j >= 1; j--)
                run(0, 1);

        for (int j = 1; j <= M; j++)
            for (int i = 1; i <= N; i++)
                run(-1, 0);

        for (int j = 1; j <= M; j++)
            for (int i = N; i >= 1; i--)
                run(1, 0);

        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                if (board[i][j] == 1)
                    board[i][j] = 0;
    }

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            maxn = max(maxn, checked[i][j]);

    maxnlen = maxn < 10 ? 2 : 3;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            output(checked[i][j]);
        }
        cout << '\n';
    }
}
