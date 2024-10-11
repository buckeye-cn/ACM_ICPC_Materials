// https://open.kattis.com/problems/boxes

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int parent[240000];
int box_count[240000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> parent[i];
    }

    for (int i = 1; i <= n; ++i) {
        for (int ii = i; ii; ii = parent[ii]) {
            box_count[ii] += 1;
        }
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int m;
        cin >> m;

        int list[m];
        for (int j = 0; j < m; ++j) {
            cin >> list[j];
        }

        int result = 0;

        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                int jj = list[j];
                int kk = list[k];

                if (box_count[jj] >= box_count[kk]) continue;

                for (; jj; jj = parent[jj]) {
                    if (jj == kk) {
                        list[j] = 0;

                        k = m;
                        break;
                    }
                }
            }

            result += box_count[list[j]];
        }

        cout << result << endl;
    }

    return 0;
}
