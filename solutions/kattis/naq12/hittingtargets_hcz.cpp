// https://open.kattis.com/problems/hittingtargets

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m;
    cin >> m;

    string shape[m];
    int value[m][4];
    for (int i = 0; i < m; ++i) {
        cin >> shape[i];

        if (shape[i][0] == 'r') {
            cin >> value[i][0] >> value[i][1] >> value[i][2] >> value[i][3];
        } else {
            cin >> value[i][0] >> value[i][1] >> value[i][2];
        }
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;

        int tot = 0;
        for (int j = 0; j < m; ++j) {
            if (shape[j][0] == 'r') {
                tot += x >= value[j][0]
                    && y >= value[j][1]
                    && x <= value[j][2]
                    && y <= value[j][3];
            } else {
                tot += sqr(x - value[j][0]) + sqr(y - value[j][1]) <= sqr(value[j][2]);
            }
        }

        cout << tot << endl;
    }

    return 0;
}
