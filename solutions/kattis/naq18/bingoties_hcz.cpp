// https://open.kattis.com/problems/bingoties

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

int n;
int games[100][5][5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < 5; ++x) {
            for (int y = 0; y < 5; ++y) {
                cin >> games[i][x][y];
            }
        }
    }

    pair<int, int> best {101, 101};

    for (int last = 1; last <= 3000; ++last) {
        int found_tot = 0;
        int found[100];
        int found_x[100];

        for (int i = 0; i < n; ++i) {
            for (int x = 0; x < 5; ++x) {
                for (int y = 0; y < 5; ++y) {
                    if (games[i][x][y] == last) {
                        found[found_tot] = i;
                        found_x[found_tot] = x;
                        found_tot += 1;
                    }
                }
            }
        }

        for (int i = 0; i < found_tot; ++i) {
            auto vi = games[found[i]];

            for (int j = i + 1; j < found_tot; ++j) {
                auto vj = games[found[j]];

                unordered_set<int> s;

                s.insert({vi[found_x[i]][0]});
                s.insert({vi[found_x[i]][1]});
                s.insert({vi[found_x[i]][2]});
                s.insert({vi[found_x[i]][3]});
                s.insert({vi[found_x[i]][4]});
                s.insert({vj[found_x[j]][0]});
                s.insert({vj[found_x[j]][1]});
                s.insert({vj[found_x[j]][2]});
                s.insert({vj[found_x[j]][3]});
                s.insert({vj[found_x[j]][4]});
                s.erase(last);

                bool fail = false;

                for (int k = 0; k < n; ++k) {
                    if (k == found[i]) continue;
                    if (k == found[j]) continue;

                    for (int x = 0; x < 5; ++x) {
                        int match = 0;

                        for (int y = 0; y < 5; ++y) {
                            match += s.find(games[k][x][y]) != s.end();
                        }

                        fail |= match == 5;
                    }
                }

                if (!fail) {
                    best = min(best, {found[i], found[j]});
                }
            }
        }
    }

    if (best.first < n) {
        cout << best.first + 1 << ' ' << best.second + 1 << endl;
    } else {
        cout << "no ties" << endl;
    }

    return 0;
}
