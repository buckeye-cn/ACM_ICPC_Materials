// https://open.kattis.com/problems/easiest

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int dsum(int n) {
    if (n) {
        return n % 10 + dsum(n / 10);
    } else {
        return 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        int n;
        cin >> n;

        if (!n) {
            return 0;
        }

        int sum = dsum(n);

        for (int i = 11; true; ++i) {
            if (dsum(i * n) == sum) {
                cout << i << endl;

                break;
            }
        }
    }
}
