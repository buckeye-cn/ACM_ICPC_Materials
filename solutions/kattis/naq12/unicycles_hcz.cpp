// https://open.kattis.com/problems/unicycles

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        int n, m;
        cin >> n >> m;

        if (cin.eof()) {
            return 0;
        }

        __int128 all = 0;

        for (int i = 0; i < m; ++i) {
            int a;
            cin >> a;

            all |= __int128(1) << a;
        }

        unordered_set<__int128> dp[m + 2];

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                __int128 item = 0;

                for (int k = j; k < n; k += i) {
                    item |= __int128(1) << k;
                }

                if ((item | all) == all) {
                    dp[1].insert(item);
                }
            }
        }

        // for (__int128 i: dp[1]) {
        //     cerr << ':' << (long) i << ' ' << (long) all << endl;
        // }

        int best = 0;

        for (int i = 1; i <= m && !best; ++i) {
            for (__int128 j: dp[i]) {
                if (j == all) {
                    best = i;
                    break;
                }

                for (__int128 k: dp[1]) {
                    dp[i + 1].insert(j | k);
                }
            }
        }

        cout << best << endl;
    }
}
