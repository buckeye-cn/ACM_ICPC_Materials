// https://open.kattis.com/problems/pizzaparty

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

bool active[1000000];
int n;
int cmd[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    unordered_map<string, int> m;

    int c;
    cin >> c;

    for (int i = 0; i < c; ++i) {
        string s;
        cin >> s;

        if (s == "if") {
            while (true) {
                cin >> s;

                int k = m.insert({s, m.size()}).first->second;

                cmd[n++] = k;

                cin >> s;

                if (s == "and") {
                    cmd[n++] = -1;
                } else if (s == "or") {
                    cmd[n++] = -2;
                } else {
                    cin >> s;

                    int k = m.insert({s, m.size()}).first->second;

                    cmd[n++] = k;

                    break;
                }
            }
        } else {
            int k = m.insert({s, m.size()}).first->second;

            active[k] = true;
        }
    }

    for (int iter = 0; iter < 1000; ++iter) {
        for (int i = 0; i < n; ++i) {
            bool a = active[cmd[i++]];

            while (cmd[i] == -1) {
                a &= active[cmd[i + 1]];
                i += 2;
            }

            while (cmd[i] == -2) {
                a |= active[cmd[i + 1]];
                i += 2;
            }

            if (a) {
                active[cmd[i]] = true;
            }
        }
    }

    int tot = 0;

    for (int i = 0; i < m.size(); ++i) {
        tot += active[i];
    }

    cout << tot << endl;

    return 0;
}
