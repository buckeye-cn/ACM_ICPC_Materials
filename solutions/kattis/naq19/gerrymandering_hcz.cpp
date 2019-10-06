// https://open.kattis.com/problems/gerrymandering

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int sum_a[1000];
int sum_b[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int p, d;
    cin >> p >> d;

    for (int i = 0; i < p; ++i) {
        int dd, a, b;
        cin >> dd >> a >> b;

        sum_a[dd - 1] += a;
        sum_b[dd - 1] += b;
    }

    int vote = 0;
    int waste_a = 0;
    int waste_b = 0;

    for (int i = 0; i < d; ++i) {
        vote += sum_a[i] + sum_b[i];

        if (sum_a[i] > sum_b[i]) {
            waste_a += sum_a[i] - (sum_a[i] + sum_b[i]) / 2 - 1;
            waste_b += sum_b[i];

            cout << "A " << sum_a[i] - (sum_a[i] + sum_b[i]) / 2 - 1 << ' ' << sum_b[i] << endl;
        } else {
            waste_a += sum_a[i];
            waste_b += sum_b[i] - (sum_a[i] + sum_b[i]) / 2 - 1;

            cout << "B " << sum_a[i] << ' ' << sum_b[i] - (sum_a[i] + sum_b[i]) / 2 - 1 << endl;
        }
    }

    cout << double(abs(waste_a - waste_b)) / vote << endl;

    return 0;
}
