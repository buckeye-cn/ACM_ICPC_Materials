// https://open.kattis.com/problems/perfectpathpatrol

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long sum_p[500000];
long max_p[500000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 1; i < n; ++i) {
        int u, v;
        long p;
        cin >> u >> v >> p;

        sum_p[u] += p;
        sum_p[v] += p;
        max_p[u] = max(max_p[u], p);
        max_p[v] = max(max_p[v], p);
    }

    long total = 0;

    for (int i = 0; i < n; ++i) {
        if (max_p[i] * 2 - sum_p[i] > 0) {
            total += max_p[i] * 2 - sum_p[i];
        } else {
            total += sum_p[i] & 1;
        }
    }

    cout << total / 2 << endl;

    return 0;
}
