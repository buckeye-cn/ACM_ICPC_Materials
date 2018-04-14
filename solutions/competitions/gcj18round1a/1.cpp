// not AC

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool data[120][120];
int sum_i[120];
int sum_j[120];
int zone_i[120];
int zone_j[120];
int zone[120][120];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        memset(data, 0, sizeof(data));
        memset(sum_i, 0, sizeof(sum_i));
        memset(sum_j, 0, sizeof(sum_j));
        memset(zone_i, 0, sizeof(zone_i));
        memset(zone_j, 0, sizeof(zone_j));
        memset(zone, 0, sizeof(zone));

        int r, c, h, v;
        cin >> r >> c >> h >> v;
        h += 1;
        v += 1;

        int n = 0;

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                char cc;
                cin >> cc;

                if (cc == '@') {
                    data[i][j] = true;
                    sum_i[i] += 1;
                    sum_j[j] += 1;
                    n += 1;
                }
            }
        }

        bool ok = n % (h * v) == 0;
        int unit = n / (h * v);

        for (int i = 0, sum = 0, k = 0; i < r; ++i) {
            sum += sum_i[i];
            zone_i[i] = k;
            if (sum == (k + 1) * (n / h)) {
                k += 1;
            } else if (sum > (k + 1) * (n / h)) {
                ok = false;
            }
        }

        for (int j = 0, sum = 0, l = 0; j < c; ++j) {
            sum += sum_j[j];
            zone_j[j] = l;
            if (sum == (l + 1) * (n / v)) {
                l += 1;
            } else if (sum > (l + 1) * (n / v)) {
                ok = false;
            }
        }

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (data[i][j]) {
                    zone[zone_i[i]][zone_j[j]] += 1;
                }
                // cerr << i << ' ' << j << ' ' << zone_i[i] << ' ' << zone_j[j] << endl;
            }
        }

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < v; ++j) {
                if (zone[i][j] != unit) {
                    ok = false;
                }
                // cerr << zone[i][j] << ' ';
            }
            // cerr << endl;
        }

        if (ok) {
            cout << "POSSIBLE" << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
