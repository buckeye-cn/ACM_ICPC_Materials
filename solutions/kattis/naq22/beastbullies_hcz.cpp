// https://open.kattis.com/problems/beastbullies

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int s[500000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }

    sort(s, s + n);

    int n_curr = 0;
    long tot_curr = 0;
    int n_next = 0;
    long tot_next = 0;

    for (int i = n - 1; i >= 0; --i) {
        n_next += 1;
        tot_next += s[i];

        if (tot_next >= tot_curr) {
            n_curr += n_next;
            tot_curr += tot_next;
            n_next = 0;
            tot_next = 0;
        }
    }

    cout << n_curr << endl;

    return 0;
}
