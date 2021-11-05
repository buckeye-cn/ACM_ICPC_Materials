// https://open.kattis.com/problems/overthehill1

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int matrix[10][10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    cin.get();

    string s;
    getline(cin, s);

    for (int i = 0; i < s.size(); i += n) {
        for (int j = 0; j < n; ++j) {
            int t = 0;

            for (int k = 0; k < n; ++k) {
                if (i + k < s.size() && s[i + k] >= 'A') {
                    t += (s[i + k] - 'A') * matrix[j][k];
                } else if (i + k < s.size() && s[i + k] >= '0') {
                    t += (s[i + k] - '0' + 26) * matrix[j][k];
                } else {
                    t += 36 * matrix[j][k];
                }
            }

            cout << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 "[t % 37];
        }
    }

    cout << endl;

    return 0;
}
