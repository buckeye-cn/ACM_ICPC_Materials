// https://open.kattis.com/problems/prefixfreecode

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD 1000000007l

using namespace std;

int nodes[1000000][26];
int order[1000000];
int minx[1000000];
int maxx[1000000];

int n, k;

int tot = 0;
long ptable[1000000];
int counts[1000000][20];

char buf[1000000];

void scan(int j) {
    while (minx[j] == maxx[j]) {
        j = nodes[j][minx[j]];
    }
    if (minx[j] > maxx[j]) {
        order[j] = ++tot;
    } else {
        for (int i = 0; i < 26; ++i) {
            if (nodes[j][i]) scan(nodes[j][i]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> k;

    ptable[n - k] = 1;
    for (int i = n - k + 1; i < n; ++i) {
        ptable[i] = ptable[i - 1] * i % 1000000007l;
    }

    cin.get();

    int node_tot = 0;

    for (int i = 0; i < n; ++i) {
        int j = 0;
        cin.getline(buf, sizeof(buf));
        for (char *c = buf; *c; ++c) {
            if (!nodes[j][*c - 'a']) {
                nodes[j][*c - 'a'] = ++node_tot;
                minx[node_tot] = 26;
                minx[j] = min(minx[j], *c - 'a');
                maxx[j] = max(maxx[j], *c - 'a');
            }
            j = nodes[j][*c - 'a'];
        }
    }

    scan(0);

    int pos = 0;
    int j = 0;
    long r = 1;
    cin.getline(buf, sizeof(buf));
    for (char *c = buf; *c; ++c) {
        j = nodes[j][*c - 'a'];
        if (order[j]) {
            int i = order[j] - 1;
            long pp = ptable[n - 1 - pos++];

            int ix = i;
            for (int bit = 0; bit < 20; ++bit) {
                if (i & (1 << bit)) {
                    ix -= counts[i & -2 << bit][bit];
                }
                counts[i & -1 << bit][bit] += 1;
            }
            r += pp * ix;

            j = 0;
        }
    }

    cout << (r % 1000000007l) << endl;

    return 0;
}
