#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool comp[100];

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

        comp[s.size() - 1] = false;

        for (int i = s.size() - 2; i >= 0; --i) {
            if (s[i] < s[i + 1]) {
                comp[i] = true;
            } else if (s[i] > s[i + 1]) {
                comp[i] = false;
            } else {
                comp[i] = comp[i + 1];
            }
        }

        for (int i = 0; i < s.size(); ++i) {
            if (comp[i]) {
                cout << s[i];
            }
            cout << s[i];
        }
        cout << endl;
    }

    return 0;
}
