// https://open.kattis.com/problems/catch

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int a[1000000];
int b[1000000];
double pp[1000000];
pair<long, int> ts[2000000];

double p_prev[2000000];
long t_prev[2000000];
double p_curr[2000000];
double p_bus[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m, n;
    long k;
    cin >> m >> n >> k;

    for (int i = 0; i < m; ++i) {
        long s, t;
        cin  >> a[i] >> b[i] >> s >> t >> pp[i];

        ts[2 * i].first = -s * 2;
        ts[2 * i].second = i;
        ts[2 * i + 1].first = -t * 2 - 1;
        ts[2 * i + 1].second = i;
    }

    sort(ts, ts + 2 * m);

    p_curr[1] = 1;

    for (int ii = 0; ii < 2 * m; ++ii) {
        int i = ts[ii].second;

        if (ts[ii].first & 1) {
            p_bus[i] = p_curr[b[i]];
        } else {
            if (t_prev[a[i]] != ts[ii].first / 2) {
                p_prev[a[i]] = p_curr[a[i]];
                t_prev[a[i]] = ts[ii].first / 2;
            }

            p_curr[a[i]] = max(
                p_curr[a[i]],
                pp[i] * p_bus[i] + (1 - pp[i]) * p_prev[a[i]]
            );
        }
    }

    cout << p_curr[0] << endl;

    return 0;
}
