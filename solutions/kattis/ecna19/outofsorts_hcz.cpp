// https://open.kattis.com/problems/outofsorts

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long x[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    long m, a, c;
    cin >> n >> m >> a >> c >> x[0];

    for (int i = 1; i <= n; ++i) {
        x[i] = (a * x[i - 1] + c) % m;
    }

    int total = 0;

    for (int i = 1; i <= n; ++i) {
        int lo = 1;
        int hi = n;

        while (true) {
            int mid = (lo + hi) >> 1;

            if (mid < i) {
                if (x[mid] < x[i]) {
                    lo = mid + 1;
                } else {
                    break;
                }
            } else if (mid > i) {
                if (x[mid] > x[i]) {
                    hi = mid - 1;
                } else {
                    break;
                }
            } else {
                total += 1;

                break;
            }
        }
    }

    cout << total << endl;

    return 0;
}
