// https://open.kattis.com/problems/oddgnome

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int n;
int data[2000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;


    for (int i = 0; i < n; ++i) {
        int tot;
        cin >> tot;

        for (int j = 0; j < tot; ++j) {
            cin >> data[j];
        }

        for (int j = 1; j < tot - 1; ++j) {
            int last = -1;
            bool ok = true;
            for (int k = 0; k < tot; ++k) {
                if (k != j) {
                    if (data[k] <= last) {
                        ok = false;
                        break;
                    }
                    last = data[k];
                }
            }
            if (ok) {
                cout << j + 1 << endl;
            }
        }
    }

    return 0;
}
