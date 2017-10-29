// https://open.kattis.com/problems/arcade

#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

int n;
int v[40][40];
double p[40][40][5];

double locate[40][40];
double fall[40][40];

double result;
double totfall;

int main() {
    ios_base::sync_with_stdio(false);
    cout.precision(10);

    cin >> n;

    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= x; ++y) {
            cin >> v[x][y];
        }
    }

    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= x; ++y) {
            cin >> p[x][y][0] >> p[x][y][1] >> p[x][y][2] >> p[x][y][3] >> p[x][y][4];
        }
    }

    locate[1][1] = 1;

    for (int i = 1; i <= 10000; ++i) {
    // for (int i = 1; i <= 5000 * (n + 1) * (n + 1); ++i) {
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= x; ++y) {
                if ((x & 1) == (i & 1)) {
                    locate[x - 1][y - 1] += locate[x][y] * p[x][y][0];
                    locate[x - 1][y] += locate[x][y] * p[x][y][1];
                    locate[x + 1][y] += locate[x][y] * p[x][y][2];
                    locate[x + 1][y + 1] += locate[x][y] * p[x][y][3];
                    fall[x][y] += locate[x][y] * p[x][y][4];
                    locate[x][y] = 0;
                }
            }
        }
    }

    // for (int x = 1; x <= n; ++x) {
    //     for (int y = 1; y <= x; ++y) {
    //         cout << fall[x][y] << ' ';
    //     }
    //     cout << endl;
    // }

    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= x; ++y) {
            totfall += fall[x][y];
            result += v[x][y] * fall[x][y];
        }
    }

    // cout << totfall << endl;
    cout << result / totfall << endl;

    return 0;
}
