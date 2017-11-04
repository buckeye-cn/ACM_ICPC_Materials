// https://open.kattis.com/problems/redrover

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int node_tot = 1;
int nodes[10240][128];
int occur[10240][128];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;
    cin >> s;

    int best = s.size();

    for (int i = 0; i < s.size(); ++i) {
        int curr = 0;

        for (int j = i; j < s.size(); ++j) {
            if (nodes[curr][int(s[j])]) {
                curr = nodes[curr][int(s[j])];
            } else {
                curr = nodes[curr][int(s[j])] = node_tot;
                node_tot += 1;
            }

            int k = 0;
            while (occur[curr][k]) ++k;
            if (!k || occur[curr][k - 1] <= i) {
                occur[curr][k] = j + 1;
                ++k;
            }

            int len = s.size() + j - i + 1 - (j - i) * k;
            if (best > len) {
                best = len;
            }
        }
    }

    // for (int i = 0; i < 50; ++i) {
    //     cout << i << ':' << 'n' << nodes[i]['N'] << 'e' << nodes[i]['E'] << 'w' << nodes[i]['W'] << 's' << nodes[i]['S'] << endl;

    //     for (int k = 0; occur[i][k]; ++k) cout << ' ' << occur[i][k];
    //     cout << endl;
    // }

    cout << best << endl;

    return 0;
}
