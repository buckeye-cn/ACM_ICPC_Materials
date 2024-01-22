// https://open.kattis.com/problems/logo2

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

const double PI = acos(-1);

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;

        double x1 = 0;
        double y1 = 0;
        double a1 = 0;
        double x2 = 0;
        double y2 = 0;
        double a2 = 0;
        string q;

        for (int j = 0; j < n; ++j) {
            string s1, s2;
            cin >> s1 >> s2;

            if (s2 == "?") {
                q = s1;

                if (q == "fd" || q == "bk") {
                    x2 = x1;
                    y2 = y1;
                    a2 = a1;
                }
            } else {
                double v = stoi(s2);

                if (q.empty()) {
                    if (s1 == "fd") {
                        x1 += v * sin(a1);
                        y1 += v * cos(a1);
                    } else if (s1 == "bk") {
                        x1 -= v * sin(a1);
                        y1 -= v * cos(a1);
                    } else if (s1 == "lt") {
                        a1 += v * PI / 180;
                    } else {
                        a1 -= v * PI / 180;
                    }
                } else if (s1 == "fd") {
                    x2 += v * sin(a2);
                    y2 += v * cos(a2);
                } else if (s1 == "bk") {
                    x2 -= v * sin(a2);
                    y2 -= v * cos(a2);
                } else if (s1 == "lt") {
                    a2 += v * PI / 180;
                } else {
                    a2 -= v * PI / 180;
                }
            }
        }

        if (q == "fd") {
            int v = round(sqrt(sqr(x2) + sqr(y2)));

            if (sqr(x2 + v * sin(a1)) + sqr(y2 + v * cos(a1)) < 1e-3) {
                cout << v << endl;
            } else {
                cout << -v << endl;
            }
        } else if (q == "bk") {
            int v = round(sqrt(sqr(x2) + sqr(y2)));

            if (sqr(x2 - v * sin(a1)) + sqr(y2 - v * cos(a1)) < 1e-3) {
                cout << v << endl;
            } else {
                cout << -v << endl;
            }
        } else if (q == "lt") {
            for (int v = 0; v < 360; ++v) {
                double a = a1 + v * PI / 180;

                if (sqr(x1 + x2 * cos(a) + y2 * sin(a)) + sqr(y1 + y2 * cos(a) - x2 * sin(a)) < 1e-3) {
                    cout << v << endl;
                }
            }
        } else {
            for (int v = 0; v < 360; ++v) {
                double a = a1 - v * PI / 180;

                if (sqr(x1 + x2 * cos(a) + y2 * sin(a)) + sqr(y1 + y2 * cos(a) - x2 * sin(a)) < 1e-3) {
                    cout << v << endl;
                }
            }
        }
    }

    return 0;
}
