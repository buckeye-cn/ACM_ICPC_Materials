// https://open.kattis.com/problems/flippingcards

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int p[50000];
int q[50000];
int vcount[100001];
int vxor[100001];
int s1[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int d = 0; d < t; ++d) {
        int n;
        cin >> n;

        memset(vcount, 0, sizeof(vcount));
        memset(vxor, 0, sizeof(vxor));

        for (int i = 0; i < n; ++i) {
            cin >> p[i] >> q[i];

            vcount[p[i]] += 1;
            vcount[q[i]] += 1;
            vxor[p[i]] ^= i;
            vxor[q[i]] ^= i;
        }

        int m = 0;

        for (int i = 1; i <= 2 * n; ++i) {
            if (vcount[i] == 1) {
                s1[m++] = i;
            }
        }

        while (m) {
            int i = vxor[s1[--m]];

            if (vcount[s1[m]] == 1) {
                vcount[p[i]] -= 1;
                vcount[q[i]] -= 1;
                vxor[p[i]] ^= i;
                vxor[q[i]] ^= i;
                s1[m++] = p[i] ^ q[i] ^ s1[m];
            }
        }

        bool ok = true;

        for (int i = 1; i <= 2 * n; ++i) {
            ok &= vcount[i] == 0 || vcount[i] == 2;
        }

        if (ok) {
            cout << "possible" << endl;
        } else {
            cout << "impossible" << endl;
        }
    }

    return 0;
}
