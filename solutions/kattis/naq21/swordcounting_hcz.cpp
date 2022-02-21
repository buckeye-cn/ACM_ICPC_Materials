// https://open.kattis.com/problems/swordcounting

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> g[100000];
vector<int> g2[100000];
char mask1[33554432];
char mask2[33554432];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int s, t;
        cin >> s >> t;
        s -= 1;
        t -= 1;

        g[s].push_back(t);
        g[t].push_back(s);

        int h1 = (min(s, t) * 1234567 + max(s, t) * 7654321) & 268435455;
        int h2 = (max(s, t) * 1234567 + min(s, t) * 7654321) & 268435455;
        mask1[h1 >> 3] |= 1 << (h1 & 7);
        mask2[h2 >> 3] |= 1 << (h2 & 7);
    }

    long total = 0;

    for (int i = 0; i < n; ++i) {
        long s1 = g[i].size();
        if (s1 < 2) continue;

        for (int j = 0; j < g[i].size(); ++j) {
            int p2 = g[i][j];
            long s2 = g[p2].size();
            if (s2 < 2) continue;

            total += (s1 - 1) * (s1 - 2) * (s1 - 3) / 6 * (s2 - 1);

            if (s1 < s2 || s1 == s2 && i < p2) {
                g2[i].push_back(p2);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        long s1 = g[i].size();

        for (int j = 0; j < g2[i].size(); ++j) {
            int p2 = g2[i][j];
            long s2 = g[p2].size();

            for (int k = 0; k < g2[p2].size(); ++k) {
                int p3 = g2[p2][k];
                long s3 = g[p3].size();

                int h1 = (min(i, p3) * 1234567 + max(i, p3) * 7654321) & 268435455;
                int h2 = (max(i, p3) * 1234567 + min(i, p3) * 7654321) & 268435455;

                if ((mask1[h1 >> 3] & (1 << (h1 & 7))) && (mask2[h2 >> 3] & (1 << (h2 & 7)))) {
                    total -= (s1 - 2) * (s1 - 3) + (s2 - 2) * (s2 - 3) + (s3 - 2) * (s3 - 3);
                }
            }
        }
    }

    cout << total << endl;

    return 0;
}
