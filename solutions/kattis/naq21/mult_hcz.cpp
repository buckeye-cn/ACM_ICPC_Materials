// https://open.kattis.com/problems/mult

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

    int first = 0;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        if (first) {
            if (x % first == 0) {
                cout << x << endl;
                first = 0;
            }
        } else {
            first = x;
        }
    }

    return 0;
}
