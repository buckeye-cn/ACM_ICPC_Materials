// https://open.kattis.com/problems/mastermind

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int slot1[128];
int slot2[128];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    string s1, s2;
    cin >> n >> s1 >> s2;

    int r = 0;
    for (int i = 0; i < n; ++i) {
        if (s1[i] == s2[i]) {
            r += 1;
        } else {
            slot1[int(s1[i])] += 1;
            slot2[int(s2[i])] += 1;
        }
    }

    int s = 0;
    for (int i = 0; i < 128; ++i) {
        s += min(slot1[i], slot2[i]);
    }

    cout << r << ' ' << s << endl;

    return 0;
}
