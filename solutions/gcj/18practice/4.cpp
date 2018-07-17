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
        cout << "Case #" << n_case << ": ";

        long n, k;
        cin >> n >> k;

        long level;
        for (level = 0; k >= (2l << level); ++level) {
            // nothing
        }

        long slot = n - (1l << level) + 1;
        long need = k - (1l << level) + 1;

        long s;
        if (need <= slot % (1l << level)) {
            s = slot / (1l << level) + 1;
        } else {
            s = slot / (1l << level);
        }

        cout << s / 2 << ' ' << (s - 1) / 2 << endl;
    }

    return 0;
}
