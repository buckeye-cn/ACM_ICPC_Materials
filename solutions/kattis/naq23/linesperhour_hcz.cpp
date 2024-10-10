// https://open.kattis.com/problems/linesperhour

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

    int n, ll;
    cin >> n >> ll;

    ll *= 5;

    int l[n];

    for (int i = 0; i < n; ++i) {
        cin >> l[i];

        for (int j = i; j > 0; --j) {
            if (l[j - 1] > l[j]) swap(l[j - 1], l[j]);
        }
    }

    int m = 0;

    for (int i = 0; i < n; ++i) {
        ll -= l[i];
        m += ll >= 0;
    }

    cout << m << endl;

    return 0;
}
