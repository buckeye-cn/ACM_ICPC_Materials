// https://open.kattis.com/problems/upsanddownsofinvesting

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

    int s, n, m;
    cin >> s >> n >> m;

    char mode = 'n';
    int inc = 0;
    int dec = 0;

    int peak = 0;
    int valley = 0;

    int v;
    cin >> v;

    for (int i = 1; i < s; ++i) {
        int new_v;
        cin >> new_v;

        if (new_v > v) {
            if (mode == 'd') {
                if (inc >= n - 1 && dec >= n - 1) {
                    peak += 1;
                }

                mode = 'i';
                inc = 1;
            } else {
                mode = 'i';
                inc += 1;
            }
        } else {
            if (mode == 'i') {
                if (inc >= m - 1 && dec >= m - 1) {
                    valley += 1;
                }

                mode = 'd';
                dec = 1;
            } else {
                mode = 'd';
                dec += 1;
            }
        }

        v = new_v;
        // cerr << v << ' ' << inc << ' ' << dec << endl;
    }

    if (mode == 'd') {
        if (inc >= n - 1 && dec >= n - 1) {
            peak += 1;
        }
    } else if (mode == 'i') {
        if (inc >= m - 1 && dec >= m - 1) {
            valley += 1;
        }
    }

    cout << peak << ' ' << valley << endl;

    return 0;
}
