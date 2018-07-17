#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        vector<int> values[2];

        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            int v;
            cin >> v;

            values[i & 1].push_back(v);
        }

        sort(values[0].begin(), values[0].end());
        sort(values[1].begin(), values[1].end());

        for (int i = 0; i < n; ++i) {
            if (i == n - 1) {
                cout << "OK" << endl;
                break;
            }

            if (values[(i + 1) & 1][(i + 1) >> 1] < values[i & 1][i >> 1]) {
                cout << i << endl;
                break;
            }
        }
    }

    return 0;
}
