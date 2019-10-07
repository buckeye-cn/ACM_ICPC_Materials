// https://open.kattis.com/problems/stopcounting

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long value[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> value[i];
    }

    double best = 0;

    double l_sum = 0;
    for (int i = 0; i < n; ++i) {
        l_sum += value[i];

        if (best < l_sum / (i + 1)) {
            best = l_sum / (i + 1);
        }
    }

    double r_sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        r_sum += value[i];

        if (best < r_sum / (n - i)) {
            best = r_sum / (n - i);
        }
    }

    cout << best << endl;

    return 0;
}
