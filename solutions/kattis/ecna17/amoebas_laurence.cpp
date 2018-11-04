#include <bits/stdc++.h>

using namespace std;

bool board[103][103];
int loopc = 0;

void loop(int i, int j) {
BE:
    board[i][j] = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (board[i + di][j + dj]) {
                i += di;
                j += dj;
                goto BE;
            }
        }
    }
    loopc++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int M, N;
    cin >> M >> N;

    cin.get();
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            board[i][j] = cin.get() == '#';
        }
        cin.get();
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (board[i][j]) {
                loop(i, j);
            }
        }
    }

    cout << loopc << endl;
}
