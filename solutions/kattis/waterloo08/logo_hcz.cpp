// https://open.kattis.com/problems/logo

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

        double x = 0;
        double y = 0;
        double a = 0;
        string q;

        for (int j = 0; j < n; ++j) {
            string s;
            int v;
            cin >> s >> v;

            if (q.empty()) {
                if (s == "fd") {
                    x += v * sin(a);
                    y += v * cos(a);
                } else if (s == "bk") {
                    x -= v * sin(a);
                    y -= v * cos(a);
                } else if (s == "lt") {
                    a += v * PI / 180;
                } else {
                    a -= v * PI / 180;
                }
            }
        }

        cout << round(sqrt(sqr(x) + sqr(y))) << endl;
    }

    return 0;
}
