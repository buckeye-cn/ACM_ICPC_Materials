// https://open.kattis.com/problems/spaceprobe

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int n, k;
long t1, t2;
long offset[10000];
long b[10000];
long e[10000];
int step[10000];

struct Comp {
    bool operator() (int x, int y) const {
        return b[step[x]] - offset[x] < b[step[y]] - offset[y]
            || (b[step[x]] - offset[x] == b[step[y]] - offset[y] && x < y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> k >> t1 >> t2;

    for (int i = 0; i < n; ++i) {
        cin >> offset[i];
    }

    for (int i = 0; i < k; ++i) {
        cin >> b[i] >> e[i];
    }

    set<int, Comp> heads;

    for (int i = 0; i < n; ++i) {
        heads.insert(i);
    }

    long result = 0;
    long limit = t1;

    while (!heads.empty()) {
        int i = *heads.begin();
        int j = *heads.rbegin();
        heads.erase(heads.begin());

        if (b[step[i]] - offset[i] >= t2) break;

        if (step[j] == step[i] && b[step[j]] - offset[j] < e[step[i]] - offset[i]) {
            // optimization for special cases

            result += max(b[step[i]] - offset[i] - limit, 0l);
            limit = max(limit, e[step[j]] - offset[j]);
            for (int l = 0; l < n; ++l) {
                step[l] += 1;
            }

            if (step[i] >= k) {
                break;
            }
        } else {
            result += max(b[step[i]] - offset[i] - limit, 0l);
            limit = max(limit, e[step[i]] - offset[i]);

            while (e[step[i]] - offset[i] <= limit && step[i] < k) {
                step[i] += 1;
            }
        }

        if (step[i] < k) {
            heads.insert(i);
        }
    }

    result += max(t2 - limit, 0l);

    cout << result / double(t2 - t1) << endl;

    return 0;
}
