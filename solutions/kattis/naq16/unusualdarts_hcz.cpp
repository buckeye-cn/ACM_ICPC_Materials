// https://open.kattis.com/problems/unusualdarts

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

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        double x[7];
        double y[7];
        double win;

        for (int j = 0; j < 7; ++j) {
            cin >> x[j] >> y[j];
        }
        cin >> win;

        int p[8];

        for (p[0] = 0; p[0] < 7; ++p[0])
        for (p[1] = 0; p[1] < 7; ++p[1])
        for (p[2] = 0; p[2] < 7; ++p[2])
        for (p[3] = 0; p[3] < 7; ++p[3])
        for (p[4] = 0; p[4] < 7; ++p[4])
        for (p[5] = 0; p[5] < 7; ++p[5])
        for (p[6] = 0; p[6] < 7; ++p[6]) {
            p[7] = p[0];

            int used = 0;
            for (int j = 0; j < 7; ++j) {
                used |= 1 << p[j];
            }
            if (used != 127) continue;

            for (int j = 0; j < 7; ++j)
            for (int k = j + 1; k < 7 && k < j + 6; ++k) {
                int a = p[j];
                int b = p[j + 1];
                int c = p[k];
                int d = p[k + 1];

                double abc = (x[a] - x[c]) * (y[b] - y[c]) - (y[a] - y[c]) * (x[b] - x[c]);
                double abd = (x[a] - x[d]) * (y[b] - y[d]) - (y[a] - y[d]) * (x[b] - x[d]);
                if (abc * abd >= 0) continue;

                double cda = (x[c] - x[a]) * (y[d] - y[a]) - (y[c] - y[a]) * (x[d] - x[a]);
                double cdb = (x[c] - x[b]) * (y[d] - y[b]) - (y[c] - y[b]) * (x[d] - x[b]);
                if (cda * cdb >= 0) continue;

                goto next;
            }

            {
                double s = 0;
                for (int j = 0; j < 7; ++j) {
                    int a = p[j];
                    int b = p[j + 1];

                    s += x[a] * y[b] - y[a] * x[b];
                }
                s *= 0.125;

                if (abs(abs(s * s * s) - win) < 0.00001) {
                    cout << (p[0] + 1);
                    for (int j = 1; j < 7; ++j) {
                        cout << ' ' << (p[j] + 1);
                    }

                    cout << endl;

                    goto done;
                }
            }

            next:;
        }

        done:;
    }

    return 0;
}
