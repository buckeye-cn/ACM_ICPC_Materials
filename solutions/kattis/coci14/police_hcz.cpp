// https://open.kattis.com/problems/police

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n, m;
int src[1001][1001];
int src_i[1000001];
int src_j[1000001];

int arr[1000];
int lis[1000];

int group[1001];
bool touch[1001];

int find(int g) {
    int root = g;

    while (root != group[root]) {
        root = group[root];
    }

    int curr = g;

    while (curr != root) {
        int prev = curr;

        curr = group[prev];
        group[prev] = root;
    }

    return root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        group[i] = i;

        for (int j = 1; j <= m; ++j) {
            int x;
            cin >> x;

            src[i][j] = x;
            src_i[x] = i;
            src_j[x] = j;
        }
    }

    int result = 0;
    bool has0 = false;

    for (int i = 1; i <= n; ++i) {
        int s = 0;
        int best = 0;

        for (int j = 1; j <= m; ++j) {
            int x;
            cin >> x;

            if (x) {
                if (i == src_i[x]) {
                    // same shelf: longest increasing subsequence

                    arr[s] = src_j[x];
                    lis[s] = 0;

                    for (int t = 0; t < s; ++t) {
                        if (arr[s] > arr[t]) {
                            lis[s] = max(lis[s], lis[t]);
                        }
                    }

                    lis[s] += 1;
                    best = max(best, lis[s]);
                    s += 1;
                } else {
                    // different shelf: union find

                    int g1 = find(i);
                    int g2 = find(src_i[x]);

                    group[max(g1, g2)] = min(g1, g2);
                    result += 1;
                }
            } else {
                // space

                int g = find(i);

                group[g] = 0;
                has0 = true;
            }
        }

        result += s - best;
        touch[i] = best < m;
    }

    for (int i = 1; i <= n; ++i) {
        if (touch[i]) {
            int g = find(i);

            if (g) {
                group[g] = 0;
                result += 1;
            }
        }
    }

    if (!has0 && result) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
