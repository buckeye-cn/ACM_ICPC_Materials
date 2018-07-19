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

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        double d;
        int n;
        cin >> d >> n;

        double best = 1e13;

        for (int i = 0; i < n; ++i) {
            double k, s;
            cin >> k >> s;

            double sx = s * d / (d - k);

            if (best > sx){
                best = sx;
            }
        }

        printf("Case #%d: %.10f\n", n_case, best);
    }

    return 0;
}
