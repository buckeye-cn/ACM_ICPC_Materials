// https://open.kattis.com/problems/easiest

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int sum_digits(long i) {
    int result = 0;

    while (i) {
        result += i % 10;
        i /= 10;
    }

    return result;
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

        int sum = sum_digits(n);

        for (int i = 11; true; ++i) {
            if (sum_digits(i * n) == sum) {
                cout << i << endl;

                break;
            }
        }
    }
}
