// https://open.kattis.com/problems/beastbullies

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

    int n;
    cin >> n;

    multiset<int> sset;

    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;

        sset.insert(-s);
    }

    int n_curr = 0;
    long tot_curr = 0;
    int n_next = 0;
    long tot_next = 0;

    for (int s: sset) {
        n_next += 1;
        tot_next -= s;

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
