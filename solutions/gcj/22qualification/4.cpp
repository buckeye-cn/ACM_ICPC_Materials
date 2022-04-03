#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long f[100001];
int p[100001];
long cmin[100001];
long csum[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int n;
        cin >> n;

        for (int i = 0; i <= n; ++i) {
            cmin[i] = 1e9;
            csum[i] = 0;
        }

        for (int i = 1; i <= n; ++i) {
            cin >> f[i];
        }

        for (int i = 1; i <= n; ++i) {
            cin >> p[i];
        }

        long tot = 0;

        for (int i = n; i >= 1; --i) {
            if (csum[i]) {
                f[i] = max(f[i], cmin[i]);
                tot += csum[i] - cmin[i];
            }

            cmin[p[i]] = min(cmin[p[i]], f[i]);
            csum[p[i]] += f[i];
        }

        tot += csum[0];

        cout << tot << endl;
    }

    return 0;
}
