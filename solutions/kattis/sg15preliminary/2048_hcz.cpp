// https://open.kattis.com/problems/2048

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int data[4][4];
    int action;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> data[i][j];
        }
    }

    cin >> action;

    int ii = "1210"[action] - '1';
    int bi = "1144"[action] - '1';
    int ei = "4312"[action] - '1';
    int di = "2200"[action] - '1';
    int jj = "2101"[action] - '1';
    int bj = "1144"[action] - '1';
    int ej = "3421"[action] - '1';
    int dj = "2200"[action] - '1';

    for (int iter = 0; iter < 4; ++iter) {
        for (int i = bi; i != ei + di; i += di) {
            for (int j = bj; j != ej + dj; j += dj) {
                if (!data[i][j]) {
                    swap(data[i][j], data[i + ii][j + jj]);
                }
            }
        }
    }

    for (int i = bi; i != ei + di; i += di) {
        for (int j = bj; j != ej + dj; j += dj) {
            if (data[i][j] == data[i + ii][j + jj]) {
                data[i][j] *= 2;
                data[i + ii][j + jj] = 0;
            }
        }
    }

    for (int iter = 0; iter < 4; ++iter) {
        for (int i = bi; i != ei + di; i += di) {
            for (int j = bj; j != ej + dj; j += dj) {
                if (!data[i][j]) {
                    swap(data[i][j], data[i + ii][j + jj]);
                }
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (j) {
                cout << ' ';
            }

            cout << data[i][j];
        }

        cout << endl;
    }

    return 0;
}
