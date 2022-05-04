// https://open.kattis.com/problems/catch

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int a[1000000];
int b[1000000];
double pp[1000000];

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

    set<pair<long, int>> ts;

    for (int i = 0; i < m; ++i) {
        long s, t;
        cin  >> a[i] >> b[i] >> s >> t >> pp[i];

        ts.insert({-s * 2, i});
        ts.insert({-t * 2 - 1, i});
    }

    p_curr[1] = 1;

    for (pair<long, int> p: ts) {
        int i = p.second;

        if (p.first & 1) {
            p_bus[i] = p_curr[b[i]];

            // cerr << 't' << -(p.first / 2) << '\t' << i << ' ' << b[i] << ' ' << p_bus[i] << endl;
        } else {
            if (t_prev[a[i]] != p.first / 2) {
                p_prev[a[i]] = p_curr[a[i]];
                t_prev[a[i]] = p.first / 2;
            }

            p_curr[a[i]] = max(
                p_curr[a[i]],
                pp[i] * p_bus[i] + (1 - pp[i]) * p_prev[a[i]]
            );

            // cerr << 's' << -(p.first / 2) << '\t' << i << ' ' << a[i] << ' ' << p_curr[a[i]] << endl;
        }
    }

    cout << p_curr[0] << endl;

    return 0;
}
