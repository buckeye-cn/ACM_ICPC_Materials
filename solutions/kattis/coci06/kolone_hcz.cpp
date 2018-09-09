// https://open.kattis.com/problems/kolone

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

    int n1, n2;
    string s1, s2;
    int t;
    cin >> n1 >> n2 >> s1 >> s2 >> t;

    for (int x = 1; x < 100; ++x) {
        int p1 = n1 - x + t;
        int p2 = x - n1;

        if (p1 >= 0 && p1 < n1) cout << s1[p1];
        if (p2 >= 0 && p2 < n2) cout << s2[p2];
    }

    cout << endl;

    return 0;
}
