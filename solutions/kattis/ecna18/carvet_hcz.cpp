// https://open.kattis.com/problems/carvet

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int v[250][250];

bool visited[250][250];
int d_i[250][250];
int d_j[250][250];
int q_i[62500];
int q_j[62500];
int head, tail;

void out(int i, int j) {
    if (v[i][j] >= 0) {
        out(d_i[i][j], d_j[i][j]);
        cout << v[i][j] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m, n;
    cin >> m >> n;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> v[i][j];

            if (v[i][j] == -1) {
                visited[i][j] = true;
                q_i[tail] = i;
                q_j[tail] = j;
                tail += 1;
            }
        }
    }

    int r, c;
    cin >> r >> c;

    while (head != tail && !visited[r - 1][c - 1]) {
        int i = q_i[head];
        int j = q_j[head];

        head += 1;

        if (i >= 2 && !visited[i - 2][j] && v[i - 1][j] == v[i - 2][j]) {
            visited[i - 2][j] = true;
            d_i[i - 2][j] = i;
            d_j[i - 2][j] = j;
            q_i[tail] = i - 2;
            q_j[tail] = j;
            tail += 1;
        }

        if (j >= 2 && !visited[i][j - 2] && v[i][j - 1] == v[i][j - 2]) {
            visited[i][j - 2] = true;
            d_i[i][j - 2] = i;
            d_j[i][j - 2] = j;
            q_i[tail] = i;
            q_j[tail] = j - 2;
            tail += 1;
        }

        if (i < m - 2 && !visited[i + 2][j] && v[i + 1][j] == v[i + 2][j]) {
            visited[i + 2][j] = true;
            d_i[i + 2][j] = i;
            d_j[i + 2][j] = j;
            q_i[tail] = i + 2;
            q_j[tail] = j;
            tail += 1;
        }

        if (j < n - 2 && !visited[i][j + 2] && v[i][j + 1] == v[i][j + 2]) {
            visited[i][j + 2] = true;
            d_i[i][j + 2] = i;
            d_j[i][j + 2] = j;
            q_i[tail] = i;
            q_j[tail] = j + 2;
            tail += 1;
        }
    }

    if (visited[r - 1][c - 1]) {
        out(d_i[r - 1][c - 1], d_j[r - 1][c - 1]);
        cout << v[r - 1][c - 1] << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
