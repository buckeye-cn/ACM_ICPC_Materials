// https://open.kattis.com/problems/mrcodeformatgrader

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int nsep;
int sep[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int c, n;
    cin >> c >> n;

    int v0;
    cin >> v0;

    sep[nsep++] = 1;

    if (v0 > 1) {
        sep[nsep++] = v0;
    }

    int last = v0;

    for (int i = 1; i < n; ++i) {
        int v;
        cin >> v;

        if (v - last > 1) {
            sep[nsep++] = last + 1;
            sep[nsep++] = v;
        }

        last = v;
    }

    sep[nsep++] = last + 1;

    if (c + 1 - last > 1) {
        sep[nsep++] = c + 1;
    }

    cout << "Errors: ";

    last = 0;

    for (int i = v0 != 1; i < nsep - 1; i += 2) {
        if (i >= 4) {
            cout << ", ";
        }

        if (i >= 2) {
            if (sep[last] == sep[last + 1] - 1) {
                cout << sep[last];
            } else {
                cout << sep[last] << '-' << sep[last + 1] - 1;
            }
        }

        last = i;
    }

    if (last) {
        cout << " and ";
    }

    if (sep[last] == sep[last + 1] - 1) {
        cout << sep[last];
    } else {
        cout << sep[last] << '-' << sep[last + 1] - 1;
    }

    cout << endl << "Correct: ";

    last = 0;

    for (int i = v0 == 1; i < nsep - 1; i += 2) {
        if (i >= 4) {
            cout << ", ";
        }

        if (i >= 2) {
            if (sep[last] == sep[last + 1] - 1) {
                cout << sep[last];
            } else {
                cout << sep[last] << '-' << sep[last + 1] - 1;
            }
        }

        last = i;
    }

    if (last) {
        cout << " and ";
    }

    if (sep[last] == sep[last + 1] - 1) {
        cout << sep[last];
    } else {
        cout << sep[last] << '-' << sep[last + 1] - 1;
    }

    cout << endl;

    return 0;
}
