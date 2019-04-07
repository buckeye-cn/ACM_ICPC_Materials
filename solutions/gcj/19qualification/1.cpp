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

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        string n;
        cin >> n;

        string r1, r2;
        for (int i = 0; i < n.size(); ++i) {
            if (n[i] == '4') {
                r1 += '2';
                r2 += '2';
            } else if (r2.size()) {
                r1 += n[i];
                r2 += '0';
            } else {
                r1 += n[i];
            }
        }

        cout << r1 << ' ' << r2 << endl;
    }

    return 0;
}
