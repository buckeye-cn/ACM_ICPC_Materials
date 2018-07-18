// https://open.kattis.com/problems/doubleclique

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n, m;
int deg[200000];
int from[200000];
int to[200000];

int limit;
int v_deg[200000];
int e_deg[200000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;

        a -= 1;
        b -= 1;

        deg[a] += 1;
        deg[b] += 1;
        from[i] = min(a, b);
        to[i] = max(a, b);
    }

    for (int i = 0; i < n; ++i) {
        v_deg[deg[i]] += 1;
    }

    limit = n - 1;
    for (int i = 0; i < m; ++i) {
        e_deg[min(deg[from[i]], deg[to[i]])] += 1;
        limit = min(limit, max(deg[from[i]], deg[to[i]]));
    }

    for (int i = n - 2; i >= 0; --i) {
        v_deg[i] += v_deg[i + 1];
        e_deg[i] += e_deg[i + 1];
    }

    for (int i = 1; i <= limit; ++i) {
        if (2 * e_deg[i] != v_deg[i] * (v_deg[i] - 1)) continue;

        int result = 1;

        for (int j = 0; j < n; ++j) {
            if (deg[j] < i) {
                if (deg[j] == v_deg[i]) {
                    result += 1;
                }
            } else {
                if (deg[j] == v_deg[i] - 1) {
                    result += 1;
                }
            }
        }

        cout << result << endl;

        return 0;
    }

    cout << 0 << endl;

    return 0;
}
