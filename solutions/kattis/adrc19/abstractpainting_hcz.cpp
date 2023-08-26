// https://open.kattis.com/problems/abstractpainting

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

    for (int d = 0; d < n; ++d) {
        int r, c;
        cin >> r >> c;

        long result = 1;

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (!i && !j) {
                    result *= 18;
                } else if (!i || !j) {
                    result *= 6;
                } else {
                    result *= 2;
                }

                result %= 1000000007;
            }
        }

        cout << result << endl;
    }

    return 0;
}
