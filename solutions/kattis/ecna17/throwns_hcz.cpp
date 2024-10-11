// https://open.kattis.com/problems/throwns

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    int pos_n = 1;
    int pos[m + 1] {0};

    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;

        if (s == "undo") {
            int j;
            cin >> j;

            pos_n -= j;
        } else {
            pos[pos_n] = pos[pos_n - 1] + stol(s);
            pos_n += 1;
        }
    }

    cout << (pos[pos_n - 1] % n + n) % n << endl;

    return 0;
}
