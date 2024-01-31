// https://open.kattis.com/problems/linesperhour

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, ll;
    cin >> n >> ll;

    ll *= 5;

    multiset<int> s;

    for (int i = 0; i < n; ++i) {
        int l;
        cin >> l;

        s.insert(l);
    }

    int m = 0;

    for (int l: s) {
        ll -= l;
        m += ll >= 0;
    }

    cout << m << endl;

    return 0;
}
