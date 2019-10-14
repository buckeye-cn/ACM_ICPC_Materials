// https://open.kattis.com/problems/prospecting

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int parent[200000];
int child_first[200000];
int child_last[200000];
int sibling[200000];
int value[200000];
int cost[200000];

bool merged[200000];

int dfs(int i) {
    int result = cost[i] - value[i];

    for (int j = child_first[i]; j; j = sibling[j]) {
        result += max(cost[j] - 1, dfs(j));
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 1; i < n; ++i) {
        cin >> parent[i] >> value[i] >> cost[i];

        if (child_first[parent[i]]) {
            sibling[child_last[parent[i]]] = i;
        } else {
            child_first[parent[i]] = i;
        }

        child_last[parent[i]] = i;

        if (value[i] == -1) {
            value[i] = 1e9;
        }
    }

    cout << dfs(0) + 1 << ' ';

    set<pair<int, int>> q;

    for (int i = 1; i < n; ++i) {
        if (cost[i] < value[i]) {
            q.insert({cost[i], i});
        }
    }

    while (value[0] < 5e8) {
        pair<int, int> p = *q.begin();
        q.erase(p);

        int i = p.second;

        while (merged[parent[i]]) {
            if (merged[parent[parent[i]]]) {
                parent[parent[i]] = parent[parent[parent[i]]];
            }

            parent[i] = parent[parent[i]];
        }

        int j = parent[i];

        if (child_first[j]) {
            sibling[child_last[j]] = child_first[i];
        } else {
            child_first[j] = child_first[i];
        }

        child_last[j] = child_last[i];

        if (cost[i] > value[j]) {
            cost[j] += cost[i] - value[j];
            value[j] = value[i];
        } else {
            value[j] += value[i] - cost[i];
        }

        if (j && cost[j] < value[j]) {
            q.insert({cost[j], j});
        }

        merged[i] = true;
    }

    cout << cost[0] << endl;

    return 0;
}
