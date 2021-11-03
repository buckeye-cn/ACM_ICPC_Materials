// https://open.kattis.com/problems/mathtrade

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

string to_str[100];
int to[100];
int depth[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    unordered_map<string, int> m;
    for (int i = 0; i < n; ++i) {
        string s1, s2;
        cin >> s1 >> s2 >> to_str[i];

        m[s2] = i;
        m.insert({to_str[i], -1});
    }

    for (int i = 0; i < n; ++i) {
        to[i] = m[to_str[i]];
    }

    int best = 0;

    for (int i = 0; i < n; ++i) {
        if (!depth[i]) {
            int step = 1;

            for (int j = i; j >= 0; j = to[j]) {
                if (depth[j]) {
                    best = max(best, step - depth[j]);
                    break;
                }

                depth[j] = step;
                step += 1;
            }
        }
    }

    if (best) {
        cout << best << endl;
    } else {
        cout << "No trades possible" << endl;
    }

    return 0;
}
