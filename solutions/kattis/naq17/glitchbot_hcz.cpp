// https://open.kattis.com/problems/glitchbot

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int x, y;
int n;
string s[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> x >> y;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }

    int best_i = 1 << 20;
    string best_ss;

    for (int k = 0; k < 3; ++k) {
        string s_replace;

        if (k == 0) {
            s_replace = "Forward";
        } else if (k == 1) {
            s_replace = "Left";
        } else if (k == 2) {
            s_replace = "Right";
        }

        for (int i = 0; i < n; ++i) {
            int xx = 0;
            int yy = 0;
            int dx = 0;
            int dy = 1;

            for (int j = 0; j < n; ++j) {
                string ss = s[j];

                if (i == j) {
                    ss = s_replace;
                }

                if (ss[0] == 'F') {
                    xx += dx;
                    yy += dy;
                } else if (ss[0] == 'L') {
                    int dx1 = -dy;
                    int dy1 = dx;
                    dx = dx1;
                    dy = dy1;
                } else {
                    int dx1 = dy;
                    int dy1 = -dx;
                    dx = dx1;
                    dy = dy1;
                }
            }

            if (xx == x && yy == y) {
                if (i < best_i) {
                    best_i = i;
                    best_ss = s_replace;
                }
                break;
            }
        }
    }

    cout << best_i + 1 << ' ' << best_ss << endl;

    return 0;
}
