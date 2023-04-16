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

        string s;
        cin >> s;

        string s1 = s;
        string s2 = s;
        int tot1 = 0;
        int tot2 = 1;

        s2[0] = 'X';

        for (int i = 1; i < s.size(); ++i) {
            if (s1[i] == s1[i - 1]) {
                s1[i] = 'X';
                tot1 += 1;
            }
            if (s2[i] == s2[i - 1]) {
                s2[i] = 'X';
                tot2 += 1;
            }
        }

        cout << min(tot1 + (s1[s.size() - 1] == s1[0]), tot2) << endl;
    }

    return 0;
}
