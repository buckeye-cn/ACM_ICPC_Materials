// https://open.kattis.com/problems/redblacktree

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD(x) ((x) % 1000000007)

using namespace std;

int n, m;
int parent[200000];
bool red[200000];

int children[200000];
int result[200000][1001];
long buf[1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;

        parent[i] = p - 1;
        children[p - 1] += 1;
    }

    for (int i = 0; i < m; ++i) {
        int r;
        cin >> r;

        red[r - 1] = true;
    }

    for (int i = 0; i < n; ++i) {
        result[i][0] = 1;
    }

    children[0] = -1; // blocking

    for (int i = 0; i < n; ++i) {
        for (int c = i, p = parent[c]; !children[c]; c = p, p = parent[c]) {
            children[c] = -1; // blocking
            result[c][red[c]] += 1;

            memset(buf, 0, sizeof(buf));

            for (int j = 0; result[p][j]; ++j) {
                for (int k = 0; result[c][k]; ++k) {
                    buf[j + k] += MOD(long(result[p][j]) * long(result[c][k]));
                }
            }

            for (int j = 0; buf[j]; ++j) {
                result[p][j] = MOD(buf[j]);
            }

            children[p] -= 1;
        }
    }

    result[0][red[0]] += 1;

    for (int i = 0; i <= m; ++i) {
        cout << result[0][i] << endl;
    }

    return 0;
}
