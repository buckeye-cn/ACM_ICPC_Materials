// https://open.kattis.com/problems/palindromicpassword

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

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;

        int best = 0;
        int best_diff = 999999;

        for (int j = 1; j <= 9; ++j) {
            for (int k = 0; k <= 9; ++k) {
                for (int l = 0; l <= 9; ++l) {
                    int p = j * 100001 + k * 10010 + l * 1100;
                    int p_diff = abs(p - value);

                    if (best_diff > p_diff) {
                        best = p;
                        best_diff = p_diff;
                    }
                }
            }
        }

        cout << best << endl;
    }

    return 0;
}
