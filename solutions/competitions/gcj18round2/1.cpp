#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char result[120][120];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int c;
        cin >> c;

        int b[c];
        for (int i = 0; i < c; ++i) {
            cin >> b[i];
        }

        if (b[0] == 0 || b[c - 1] == 0) {
            cout << "IMPOSSIBLE" << endl;

            continue;
        }

        int final_pos[c];
        int j = 0;
        for (int i = 0; i < c; ++i) {
            for (int k = b[i]; k > 0; --k) {
                final_pos[j++] = i;
            }
        }

        int pos[c];
        for (int i = 0; i < c; ++i) {
            pos[i] = i;
        }

        for (int i = 0; true; ++i) {
            for (int j = 0; j < c; ++j) {
                result[i][j] = '.';
            }
            result[i][c] = '\0';

            bool changed = false;

            for (int j = 0; j < c; ++j) {
                if (pos[j] < final_pos[j]) {
                    result[i][pos[j]] = '\\';
                    pos[j] += 1;
                    changed = true;
                } else if (pos[j] > final_pos[j]) {
                    result[i][pos[j]] = '/';
                    pos[j] -= 1;
                    changed = true;
                }
            }

            if (!changed) {
                cout << (i + 1) << endl;
                for (int j = 0; j <= i; ++j) {
                    cout << result[j] << endl;
                }

                break;
            }
        }
    }

    return 0;
}
