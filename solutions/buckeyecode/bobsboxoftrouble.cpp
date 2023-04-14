#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

uint64_t cumxor[5000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int x, y, z, q;
    cin >> x >> y >> z >> q;

    for (int i = 1; i <= x; ++i) {
        for (int j = 1; j <= y; ++j) {
            for (int k = 1; k <= z; ++k) {
                int v;
                cin >> v;
                cumxor[i * (y + 1) * (z + 1) + j * (z + 1) + k] = (v + 2) * 1234567891234567ul;
            }
        }
    }

    for (int i = 1; i <= x; ++i) {
        for (int j = 1; j <= y; ++j) {
            for (int k = 1; k <= z; ++k) {
                cumxor[i * (y + 1) * (z + 1) + j * (z + 1) + k] ^= cumxor[i * (y + 1) * (z + 1) + j * (z + 1) + k - 1];
            }
        }
    }

    for (int i = 1; i <= x; ++i) {
        for (int j = 1; j <= y; ++j) {
            for (int k = 1; k <= z; ++k) {
                cumxor[i * (y + 1) * (z + 1) + j * (z + 1) + k] ^= cumxor[i * (y + 1) * (z + 1) + (j - 1) * (z + 1) + k];
            }
        }
    }

    for (int i = 1; i <= x; ++i) {
        for (int j = 1; j <= y; ++j) {
            for (int k = 1; k <= z; ++k) {
                cumxor[i * (y + 1) * (z + 1) + j * (z + 1) + k] ^= cumxor[(i - 1) * (y + 1) * (z + 1) + j * (z + 1) + k];
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b, c, d, e, f;
        cin >> a >> b >> c >> d >> e >> f;
        a -= 1;
        b -= 1;
        c -= 1;

        uint64_t h = cumxor[d * (y + 1) * (z + 1) + e * (z + 1) + f]
            ^ cumxor[a * (y + 1) * (z + 1) + e * (z + 1) + f]
            ^ cumxor[d * (y + 1) * (z + 1) + b * (z + 1) + f]
            ^ cumxor[d * (y + 1) * (z + 1) + e * (z + 1) + c]
            ^ cumxor[a * (y + 1) * (z + 1) + b * (z + 1) + f]
            ^ cumxor[a * (y + 1) * (z + 1) + e * (z + 1) + c]
            ^ cumxor[d * (y + 1) * (z + 1) + b * (z + 1) + c]
            ^ cumxor[a * (y + 1) * (z + 1) + b * (z + 1) + c];

        if (h) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }

    return 0;
}
