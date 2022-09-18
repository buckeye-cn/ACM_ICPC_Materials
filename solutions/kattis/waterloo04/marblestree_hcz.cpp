// https://open.kattis.com/problems/marblestree

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool seen[10000];
int value[10000];
vector<vector<int>> child;
int total;

void dfs(int i) {
    for (int j: child[i]) {
        dfs(j);
        value[i] += value[j];
    }

    total += abs(value[i]);
}

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

        memset(seen, 0, sizeof(seen));
        memset(value, 0, sizeof(value));
        child.clear();
        total = 0;

        for (int i = 0; i < n; ++i) {
            int v, m, d;
            cin >> v >> m >> d;

            value[i] = m - 1;
            child.push_back({});

            for (int j = 0; j < d; ++j) {
                int k;
                cin >> k;

                child[i].push_back(k - 1);
                seen[k - 1] = true;
            }
        }

        for (int i = 0; i < n; ++i) {
            if (!seen[i]) {
                dfs(i);
            }
        }

        cout << total << endl;
    }
}
