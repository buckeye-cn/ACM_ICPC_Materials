// https://open.kattis.com/problems/bigtruck

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;
int item[20000];
int nline;
// (from, to, weight) tuples
int line[20000][3];

int len[20000];
int pick[20000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> item[i];
        len[i] = 1 << 30;
    }

    cin >> nline;

    for (int i = 0; i < nline; ++i) {
        cin >> line[i][0];
        cin >> line[i][1];
        cin >> line[i][2];
    }

    len[0] = 0;
    pick[0] = item[0];

    for (int j = 0; j < n + 1; ++j)
    for (int i = 0; i < nline; ++i) {
        int a = line[i][0] - 1;
        int b = line[i][1] - 1;
        int v = line[i][2];

        if (len[a] > len[b] + v) {
            len[a] = len[b] + v;
            pick[a] = pick[b] + item[a];
        } else if (len[a] == len[b] + v && pick[a] < pick[b] + item[a]) {
            pick[a] = pick[b] + item[a];
        }
        if (len[b] > len[a] + v) {
            len[b] = len[a] + v;
            pick[b] = pick[a] + item[b];
        } else if (len[b] == len[a] + v && pick[b] < pick[a] + item[b]) {
            pick[b] = pick[a] + item[b];
        }
    }

    if (len[n - 1] < 1 << 30) {
        cout << len[n - 1] << ' ' << pick[n - 1] << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
