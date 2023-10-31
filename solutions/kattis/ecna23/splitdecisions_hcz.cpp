// https://open.kattis.com/problems/splitdecisions

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

string wlist[1500];
bool ok[1500][1500];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> wlist[i];
    }

    for (int i = 3; i <= 20; ++i) {
        for (int j = 0; j <= i - 2; ++j) {
            unordered_set<string> vset[26][26];

            for (int k = 0; k < n; ++k) {
                if (wlist[k].size() != i) continue;

                char c1 = wlist[k][j];
                char c2 = wlist[k][j + 1];

                wlist[k][j] = '_';
                wlist[k][j + 1] = '_';

                vset[c1 - 'A'][c2 - 'A'].insert(wlist[k]);

                wlist[k][j] = c1;
                wlist[k][j + 1] = c2;
            }

            for (int k = 0; k < n; ++k) {
                if (wlist[k].size() != i) continue;

                char c1 = wlist[k][j];
                char c2 = wlist[k][j + 1];

                wlist[k][j] = '_';
                wlist[k][j + 1] = '_';

                for (int l = k + 1; l < n; ++l) {
                    if (wlist[l].size() != i) continue;

                    char c3 = wlist[l][j];
                    char c4 = wlist[l][j + 1];

                    if (c1 == c3 || c2 == c4) continue;

                    wlist[l][j] = '_';
                    wlist[l][j + 1] = '_';

                    if (wlist[k] == wlist[l]) {
                        int overlap = 0;

                        for (const string &s: vset[c1 - 'A'][c2 - 'A']) {
                            overlap += vset[c3 - 'A'][c4 - 'A'].find(s) != vset[c3 - 'A'][c4 - 'A'].end();
                        }

                        if (overlap == 1) {
                            // cerr << wlist[k] << ' ' << wlist[l] << ' ' << j << endl;
                            ok[k][l] = true;
                        }
                    }

                    wlist[l][j] = c3;
                    wlist[l][j + 1] = c4;
                }

                wlist[k][j] = c1;
                wlist[k][j + 1] = c2;
            }
        }
    }

    int result = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            result += ok[i][j];
        }
    }

    cout << result << endl;

    return 0;
}
