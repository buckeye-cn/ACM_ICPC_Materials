// https://open.kattis.com/problems/score

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

    int h_s = 0;
    int a_s = 0;
    int t = 0;
    int h_t = 0;
    int a_t = 0;

    for (int i = 0; i < n; ++i) {
        char team;
        int s;
        int mm;
        char tmp;
        int ss;
        cin >> team >> s >> mm >> tmp >> ss;

        int new_t = mm * 60 + ss;

        if (h_s > a_s) {
            h_t += new_t - t;
        } else if (a_s > h_s) {
            a_t += new_t - t;
        }

        if (team == 'H') {
            h_s += s;
        } else {
            a_s += s;
        }
        t = new_t;
    }

    if (h_s > a_s) {
        h_t += 32 * 60 - t;
    } else if (a_s > h_s) {
        a_t += 32 * 60 - t;
    }

    printf("%c %d:%02d %d:%02d\n", "AH"[h_s > a_s], h_t / 60, h_t % 60, a_t / 60, a_t % 60);

    return 0;
}
