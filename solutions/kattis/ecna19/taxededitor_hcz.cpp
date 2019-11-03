// https://open.kattis.com/problems/taxededitor

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

vector<long> ll[10001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        long l, d;
        cin >> l >> d;

        ll[d].push_back(l);
    }

    long result = 0;

    for (long step = 1l << 46; step; step >>= 1) {
        long new_result = result | step;

        int removed = 0;
        long total = 0;
        multiset<long> s;

        for (long d = 1; d <= 10000 && removed <= m; ++d) {
            if (ll[d].empty()) continue;

            for (long l: ll[d]) {
                total += l;
                s.insert(-l);
            }

            while (total > d * new_result) {
                removed += 1;
                total += *s.begin();
                s.erase(s.begin());
            }
        }

        if (removed > m) {
            result = new_result;
        }
    }

    cout << result + 1 << endl;

    return 0;
}
