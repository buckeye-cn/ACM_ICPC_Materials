// https://open.kattis.com/problems/colorfultrees

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

int c[100001];
int c_count[100001];
int a[100000];
int b[100000];
vector<int> edges[100001];
long psum[100000];

unordered_map<int, int> dfs(int curr, int edge) {
    unordered_map<int, int> curr_m {{c[curr], 1}};

    psum[edge] = c_count[c[curr]] - 1;

    for (int j: edges[curr]) {
        if (j == edge) continue;

        int child = curr ^ a[j] ^ b[j];
        unordered_map<int, int> child_m = dfs(child, j);

        if (curr_m.size() < child_m.size()) {
            swap(curr_m, child_m);
            psum[edge] = psum[j];
        }

        for (pair<int, int> p: child_m) {
            int &count = curr_m[p.first];

            psum[edge] -= long(count) * (c_count[p.first] - count);
            count += p.second;
            psum[edge] += long(count) * (c_count[p.first] - count);

            if (count == c_count[p.first]) {
                curr_m.erase(p.first);
            }
        }
    }

    return curr_m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> c[i];

        c_count[c[i]] += 1;
    }

    for (int i = 1; i < n; ++i) {
        cin >> a[i] >> b[i];

        edges[a[i]].push_back(i);
        edges[b[i]].push_back(i);
    }

    dfs(1, 0);

    for (int i = 1; i < n; ++i) {
        cout << psum[i] << endl;
    }

    return 0;
}
