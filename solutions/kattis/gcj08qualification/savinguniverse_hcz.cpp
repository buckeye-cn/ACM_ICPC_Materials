// https://open.kattis.com/problems/savinguniverse

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int ss[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        int s;
        cin >> s;
        cin.get();

        for (int i = 0; i < s; ++i) {
            string line;
            getline(cin, line);

            ss[i] = hash<string>()(line);
        }

        int tot = 0;
        __int128 mask = 0;

        int q;
        cin >> q;
        cin.get();

        for (int i = 1; i <= q; ++i) {
            string line;
            getline(cin, line);

            int h = hash<string>()(line);

            for (int j = 0; j < s; ++j) {
                if (ss[j] == h) {
                    mask |= __int128(1) << j;

                    if (mask == (__int128(1) << s) - 1) {
                        tot += 1;
                        mask = __int128(1) << j;
                    }
                }
            }
        }

        cout << "Case #" << n_case << ": " << tot << endl;
    }

    return 0;
}
