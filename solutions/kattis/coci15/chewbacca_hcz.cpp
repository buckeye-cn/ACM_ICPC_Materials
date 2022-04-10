// https://open.kattis.com/problems/chewbacca

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

    long n;
    int k, q;
    cin >> n >> k >> q;

    for (int i = 0; i < q; ++i) {
        long a, b;
        cin >> a >> b;

        int r = 0;

        while (a != b) {
            if (a > b) {
                a = (a + k - 2) / k;
            } else {
                b = (b + k - 2) / k;
            }

            r += 1;
        }

        cout << r << endl;
    }

    return 0;
}
