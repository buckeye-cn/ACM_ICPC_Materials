// https://open.kattis.com/problems/beekeeper

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

    while (true) {
        int n;
        cin >> n;

        if (!n) {
            return 0;
        }

        int best_total = -1;
        string best_s;

        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;

            int total = 0;
            char last = '_';

            for (char c: s) {
                total += c == last && (
                    c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y'
                );

                last = c;
            }

            if (best_total < total) {
                best_total = total;
                best_s = s;
            }
        }

        cout << best_s << endl;
    }
}
