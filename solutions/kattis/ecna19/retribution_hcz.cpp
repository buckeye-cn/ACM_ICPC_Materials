// https://open.kattis.com/problems/retribution

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

int x[3][1000];
int y[3][1000];
bool used[4][1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n[3];
    cin >> n[0] >> n[1] >> n[2];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n[i]; ++j) {
            cin >> x[i][j] >> y[i][j];
        }
    }

    double total = 0;

    for (int i = 1; i < 3; ++i) {
        set<pair<int, pair<int, int>>> q;

        for (int j = 0; j < n[0]; ++j) {
            for (int k = 0; k < n[i]; ++k) {
                q.insert({sqr(x[0][j] - x[i][k]) + sqr(y[0][j] - y[i][k]), {j, k}});
            }
        }

        for (pair<int, pair<int, int>> p: q) {
            if (used[i - 1][p.second.first]) continue;
            if (used[i + 1][p.second.second]) continue;

            total += sqrt(p.first);
            used[i - 1][p.second.first] = true;
            used[i + 1][p.second.second] = true;
        }
    }

    cout << total << endl;

    return 0;
}
