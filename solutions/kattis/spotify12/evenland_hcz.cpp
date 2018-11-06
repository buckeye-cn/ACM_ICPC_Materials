// https://open.kattis.com/problems/evenland

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD(x) ((x) % 1000000009)

using namespace std;

int n, m;
int uf[100000];

int find(int i) {
    if (uf[i] == i) return i;

    return uf[i] = find(uf[i]);
}

void merge(int from, int to) {
    from = find(from);
    to = find(to);

    if (from != to) {
        uf[from] = to;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        uf[i] = i;
    }

    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;

        merge(from - 1, to - 1);
    }

    int power = m - n;

    for (int i = 0; i < n; ++i) {
        if (uf[i] == i) power += 1;
    }

    long result = 1;

    for (int i = 0; i < power; ++i) {
        result = MOD(2 * result);
    }

    cout << result << endl;

    return 0;
}
