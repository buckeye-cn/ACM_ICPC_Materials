// https://open.kattis.com/problems/restroommonitor

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int cnt_y[100000];
int cnt_n[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int s, n;
    cin >> s >> n;

    for (int i = 0; i < n; ++i) {
        int d;
        char c;
        cin >> d >> c;

        if (c == 'y') {
            cnt_y[min(d, 100000) - 1] += 1;
        } else {
            cnt_n[min(d, 100000) - 1] += 1;
        }
    }

    long remain_y = 0;
    long remain_yn = 0;

    for (int i = 0; i < 100000; ++i) {
        remain_y += 1 - cnt_y[i];
        remain_yn += s - cnt_y[i] - cnt_n[i];

        if (remain_y < 0 || remain_yn < 0) {
            cout << "No" << endl;

            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}
