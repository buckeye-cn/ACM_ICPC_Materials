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

        int x, y;
        cin >> x >> y;

        string s;
        cin >> s;

        int vc = 0;
        int vj = 0;

        for (int i = 1; i < s.size(); ++i) {
            int new_vc;
            int new_vj;

            if (s[i - 1] == 'C' && s[i] == 'C') {
                new_vc = vc;
                new_vj = 1e9;
            } else if (s[i - 1] == 'C' && s[i] == 'J') {
                new_vc = 1e9;
                new_vj = vc + x;
            } else if (s[i - 1] == 'C' && s[i] == '?') {
                new_vc = vc;
                new_vj = vc + x;
            } else if (s[i - 1] == 'J' && s[i] == 'C') {
                new_vc = vj + y;
                new_vj = 1e9;
            } else if (s[i - 1] == 'J' && s[i] == 'J') {
                new_vc = 1e9;
                new_vj = vj;
            } else if (s[i - 1] == 'J' && s[i] == '?') {
                new_vc = vj + y;
                new_vj = vj;
            } else if (s[i - 1] == '?' && s[i] == 'C') {
                new_vc = min(vc, vj + y);
                new_vj = 1e9;
            } else if (s[i - 1] == '?' && s[i] == 'J') {
                new_vc = 1e9;
                new_vj = min(vc + x, vj);
            } else if (s[i - 1] == '?' && s[i] == '?') {
                new_vc = min(vc, vj + y);
                new_vj = min(vc + x, vj);
            }

            vc = new_vc;
            vj = new_vj;
        }

        cout << min(vc, vj) << endl;
    }

    return 0;
}
