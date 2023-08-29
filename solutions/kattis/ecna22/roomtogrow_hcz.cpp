// https://open.kattis.com/problems/roomtogrow

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int d[5001];
int r[5001];
int t[5001];
int tmax[5001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> d[i] >> r[i];
        t[i] = 1;
        tmax[i] = max(tmax[i - 1], 1);

        for (int j = i - 1; tmax[j] >= t[i]; --j) {
            if (d[i] - d[j] > max(r[i], r[j])) {
                t[i] = max(t[i], t[j] + 1);
                tmax[i] = max(tmax[i], t[i]);
            }
        }
    }

    cout << n - tmax[n] << endl;

    return 0;
}
