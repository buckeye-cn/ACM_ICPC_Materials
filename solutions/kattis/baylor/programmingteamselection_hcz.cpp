// https://open.kattis.com/problems/programmingteamselection

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
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

        unordered_map<string, int> m;
        bool edge1[15][15];
        int v = 0;
        int group[15][15][15];
        bool edge2[455][455];

        memset(edge1, 0, sizeof(edge1));
        memset(group, -1, sizeof(group));
        memset(edge2, 0, sizeof(edge2));

        for (int i = 0; i < n; ++i) {
            string s1, s2;
            cin >> s1 >> s2;

            m.insert({s1, m.size()});
            m.insert({s2, m.size()});

            edge1[m[s1]][m[s2]] = true;
            edge1[m[s2]][m[s1]] = true;
        }

        for (int i = 0; i < 15; ++i) {
            for (int j = i + 1; j < 15; ++j) {
                for (int k = j + 1; k < 15; ++k) {
                    if (edge1[i][j] && edge1[j][k] && edge1[i][k]) {
                        group[i][j][k] = v;
                        v += 1;

                        // cerr << i << j << k << endl;
                    }
                }
            }
        }

        for (int i = 0; i < 15; ++i) {
            for (int j = i + 1; j < 15; ++j) {
                for (int k = j + 1; k < 15; ++k) {
                    int v1 = group[i][j][k];
                    if (v1 == -1) continue;

                    for (int s = i + 1; s < 15; ++s) {
                        if (s == j || s == k) continue;

                        for (int t = s + 1; t < 15; ++t) {
                            if (t == j || t == k) continue;

                            for (int r = t + 1; r < 15; ++r) {
                                if (r == j || r == k) continue;

                                int v2 = group[s][t][r];
                                if (v2 == -1) continue;

                                edge2[v1][v2] = true;
                                edge2[v2][v1] = true;

                                // cerr << v1 << v2 << endl;
                            }
                        }
                    }
                }
            }
        }

        bool done = false;

        for (int i = 0; i < v && !done; ++i) {
            done |= m.size() == 3;

            for (int j = i + 1; j < v; ++j) {
                if (!edge2[i][j]) continue;
                done |= m.size() == 6;

                for (int k = j + 1; k < v; ++k) {
                    if (!edge2[i][k] || !edge2[j][k]) continue;
                    done |= m.size() == 9;

                    for (int s = k + 1; s < v; ++s) {
                        if (!edge2[i][s] || !edge2[j][s] || !edge2[k][s]) continue;
                        done |= m.size() == 12;

                        for (int t = s + 1; t < v; ++t) {
                            if (!edge2[i][t] || !edge2[j][t] || !edge2[k][t] || !edge2[s][t]) continue;
                            done |= m.size() == 15;
                        }
                    }
                }
            }
        }

        if (done) {
            cout << "possible" << endl;
        } else {
            cout << "impossible" << endl;
        }
    }
}
