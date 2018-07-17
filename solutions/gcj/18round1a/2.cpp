#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int r, c;
long b;
long m[1200];
long s[1200];
long p[1200];

long solve(long t) {
    multiset<long> q;

    for (int i = 0; i < c; ++i) {
        q.insert(max(min((t - p[i]) / s[i], m[i]), 0l));
    }

    long tot = 0;
    long count = 0;

    for (auto i = q.rbegin(); i != q.rend() && count < r; ++i, ++count) {
        tot += *i;
    }

    return tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        cin >> r >> b >> c;

        for (int i = 0; i < c; ++i) {
            cin >> m[i] >> s[i] >> p[i];
        }

        long result = 0;
        for (long step = 1l << 62; step; step >>= 1) {
            if (solve(result + step) < b) {
                result += step;
            }
        }

        cout << (result + 1) << endl;
    }

    return 0;
}
