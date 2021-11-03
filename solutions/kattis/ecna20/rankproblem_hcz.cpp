// https://open.kattis.com/problems/rankproblem

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

    int rank[n + 1];
    for (int i = 1; i <= n; ++i) {
        rank[i] = i;
    }

    for (int i = 0; i < m; ++i) {
        char t;
        int a, b;
        cin >> t >> a >> t >> b;

        int ra = rank[a];
        int rb = rank[b];

        if (ra > rb) {
            for (int j = 1; j <= n; ++j) {
                if (rank[j] > rb && rank[j] <= ra) {
                    rank[j] -= 1;
                }
            }

            rank[b] = ra;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }

        for (int j = 1; j <= n; ++j) {
            if (rank[j] == i) {
                cout << 'T' << j;
            }
        }
    }

    cout << endl;

    return 0;
}
