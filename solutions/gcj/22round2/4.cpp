#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int offset[100001] {100000};
long cost[2][100001];
int jump[200001];
long dp[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int n;
        long c;
        cin >> n >> c;

        set<pair<long, bool>> xs[2];

        for (int i = 0; i < n; ++i) {
            long x;
            bool s;
            cin >> x >> s;

            xs[x < 0].insert({abs(x), s});
        }

        long total = 0;

        for (int i = 0; i <= 1; ++i) {
            int pos = 0;

            jump[offset[0]] = 0;

            for (pair<long, bool> p: xs[i]) {
                pos += 1;

                dp[pos] = dp[pos - 1] + p.first * 2;

                if (pos >= 2) {
                    dp[pos] = min(dp[pos], dp[pos - 2] + p.first * 2 + c);
                }

                offset[pos] = offset[pos - 1] + (p.second ? 1 : -1);
                cost[!p.second][pos] = cost[!p.second][pos - 1];
                cost[p.second][pos] = cost[p.second][pos - 1] + 2 * p.first;

                int prev = jump[offset[pos]];

                if (prev < pos && offset[prev] == offset[pos]) {
                    dp[pos] = min(dp[pos], dp[prev] + cost[p.second][pos] - cost[p.second][prev]);
                }

                jump[offset[pos]] = pos;
            }

            total += dp[pos];
        }

        cout << total << endl;
    }

    return 0;
}
