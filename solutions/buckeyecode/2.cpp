#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int r[1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    r[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = n; j >= 1; --j) {
            for (int k = j - i; k >= 0; k -= i) {
                r[j] += r[k];

                if (r[j] > 1000000007) {
                    r[j] -= 1000000007;
                }
            }
        }
    }

    cout << r[n] - 1 << endl;

    return 0;
}
