// https://open.kattis.com/problems/missinggnomes

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int g[120000];
bool exist[120000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        cin >> g[i];
        exist[g[i]] = true;
    }
    g[m] = n + 1;

    int pos = 0;

    for (int i = 1; i <= n; ++i) {
        if (exist[i]) {
            continue;
        }

        while (i > g[pos]) {
            printf("%d\n", g[pos++]);
        }

        printf("%d\n", i);
    }

    while (pos < m) {
        printf("%d\n", g[pos++]);
    }

    return 0;
}
