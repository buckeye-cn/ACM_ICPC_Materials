// https://naq17.kattis.com/problems/companypicnic

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int n;

int ceo;
string name[1200];
float speed[1200];
string supervisor[1200];
map<string, int> name_to_index;

int edge_tot[1200];
int edge[1200][1200];

pair<int, float> best_unused[1200];
pair<int, float> best_used[1200];

void dfs(int node) {
    for (int i = 0; i < edge_tot[node]; ++i) {
        int j = edge[node][i];

        dfs(j);

        best_unused[node].first += best_used[j].first;
        best_unused[node].second += best_used[j].second;
    }
    best_used[node] = best_unused[node];

    for (int i = 0; i < edge_tot[node]; ++i) {
        int j = edge[node][i];

        pair<int, float> new_value = best_unused[node];

        new_value.first += best_unused[j].first;
        new_value.first -= best_used[j].first;
        new_value.first += 1;
        new_value.second += best_unused[j].second;
        new_value.second -= best_used[j].second;
        new_value.second += min(speed[node], speed[j]);

        if (
            best_used[node].first < new_value.first || (
                best_used[node].first == new_value.first
                && best_used[node].second < new_value.second
            )
        ) {
            best_used[node] = new_value;
        }
    }

    // cout << name[node] << ' ' << best_unused[node].second << ' ' << best_used[node].second << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> name[i] >> speed[i] >> supervisor[i];

        name_to_index.insert({name[i], i});
    }

    for (int i = 0; i < n; ++i) {
        if (supervisor[i] == "CEO") {
            ceo = i;
        } else {
            int j = name_to_index[supervisor[i]];

            edge[j][edge_tot[j]++] = i;
        }
    }

    dfs(ceo);

    cout << best_used[ceo].first << ' ' << best_used[ceo].second / best_used[ceo].first << endl;

    return 0;
}
