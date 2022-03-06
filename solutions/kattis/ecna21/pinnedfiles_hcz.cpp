// https://open.kattis.com/problems/pinnedfiles

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int v1[100];
int v2[100];
bool seen[101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int p1, u1;
    cin >> p1 >> u1;

    int n = p1 + u1;

    for (int i = 0; i < n; ++i) {
        cin >> v1[i];
    }

    int p2, u2;
    cin >> p2 >> u2;

    for (int i = 0; i < n; ++i) {
        cin >> v2[i];
    }

    int total = 0;
    bool ok = true;

    for (int i = 0; i < p2; ++i) {
        for (int j = 0; j < n; ++j) {
            if (v1[j] == v2[i]) {
                if ((j < p1) == (i < p2)) {
                    for (int k = j + 1; k < p1; ++k) {
                        ok &= !seen[v1[k]];
                    }

                    if (!ok) {
                        total += 2;
                    }

                    seen[v2[i]] = true;
                } else {
                    total += 1;
                    ok = false;
                }
            }
        }
    }

    ok = true;

    for (int i = n - 1; i >= p2; --i) {
        for (int j = 0; j < n; ++j) {
            if (v1[j] == v2[i]) {
                if ((j < p1) == (i < p2)) {
                    for (int k = p1; k < j; ++k) {
                        ok &= !seen[v1[k]];
                    }

                    if (!ok) {
                        total += 2;
                    }

                    seen[v2[i]] = true;
                } else {
                    total += 1;
                    ok = false;
                }
            }
        }
    }

    cout << total << endl;

    return 0;
}
