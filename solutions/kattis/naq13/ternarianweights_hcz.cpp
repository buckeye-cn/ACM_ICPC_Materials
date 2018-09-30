// https://open.kattis.com/problems/ternarianweights

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int pow3[20] {1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 1; i < 20; ++i) {
        pow3[i] = pow3[i - 1] * 3;
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        int digits[20];
        for (int j = 0; j < 20; ++j) {
            digits[j] = (x + 1) % 3 - 1;
            x = (x + 1) / 3;
        }

        if (i) {
            cout << endl;
        }

        cout << "left pan:";
        for (int j = 19; j >= 0; --j) {
            if (digits[j] == -1) {
                cout << ' ' << pow3[j];
            }
        }
        cout << endl;

        cout << "right pan:";
        for (int j = 19; j >= 0; --j) {
            if (digits[j] == 1) {
                cout << ' ' << pow3[j];
            }
        }
        cout << endl;
    }

    return 0;
}
