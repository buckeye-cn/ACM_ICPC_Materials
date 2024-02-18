// https://open.kattis.com/problems/donthungertogether

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int q[1000000];
int f[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        cin >> q[i] >> f[i];
    }

    double best = 0;

    for (double d = 1e9; d >= 1e-9; d /= 2) {
        double test = best + d;

        map<int, double> stk;

        for (int i = 0; i < n; ++i) {
            stk[f[i]] += q[i];

            double remain = test;

            while (!stk.empty()) {
                if (stk.begin()->first <= i) {
                    stk.erase(stk.begin());
                } else if (remain >= stk.begin()->second) {
                    remain -= stk.begin()->second;
                    stk.erase(stk.begin());
                } else {
                    stk.begin()->second -= remain;
                    remain = 0;
                    break;
                }
            }

            if (remain > 0) {
                test = best;
                break;
            }
        }

        best = test;
    }

    if (best > 0) {
        cout << best / k << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
