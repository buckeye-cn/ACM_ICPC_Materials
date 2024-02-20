// https://open.kattis.com/problems/evenland

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD 1000000009l

using namespace std;

int n, m;
int group[100000];

int find(int g) {
    int root = g;

    while (root != group[root]) {
        root = group[root];
    }

    int curr = g;

    while (curr != root) {
        int prev = curr;

        curr = group[prev];
        group[prev] = root;
    }

    return root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        group[i] = i;
    }

    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;

        from = find(from - 1);
        to = find(to - 1);

        if (from != to) {
            group[from] = to;
        }
    }

    int power = m - n;

    for (int i = 0; i < n; ++i) {
        power += group[i] == i;
    }

    long result = 1;

    for (int i = 0; i < power; ++i) {
        result = 2 * result % MOD;
    }

    cout << result << endl;

    return 0;
}
