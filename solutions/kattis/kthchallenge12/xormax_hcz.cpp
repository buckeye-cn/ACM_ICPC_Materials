// https://open.kattis.com/problems/xormax

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long vec[60];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        long value;
        cin >> value;

        for (int j = 59; j >= 0; --j) {
            if (value >> j) {
                if (vec[j]) {
                    value ^= vec[j];
                } else {
                    vec[j] = value;
                    break;
                }
            }
        }
    }

    long result = 0;

    for (int i = 59; i >= 0; --i) {
        result = max(result, result ^ vec[i]);
    }

    cout << result << endl;

    return 0;
}
