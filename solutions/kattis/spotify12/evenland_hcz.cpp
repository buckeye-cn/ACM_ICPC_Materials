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
int group[100001];

int find(int i) {
    if (!group[i]) return i;

    return group[i] = find(group[i]);
}

void join(int from, int to) {
    from = find(from);
    to = find(to);

    if (from != to) {
        group[from] = group[to];
        group[to] = from;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;

        join(from, to);
    }

    int power = m - n;

    for (int i = 1; i <= n; ++i) {
        if (!group[i]) power += 1;
    }

    long result = 1;

    for (int i = 0; i < power; ++i) {
        result = MOD(2 * result);
    }

    cout << result << endl;

    return 0;
}
