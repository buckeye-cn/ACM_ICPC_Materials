// https://open.kattis.com/problems/vennintervals

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

int k[4000];
long h[4000];
int n_to[4000];
int to[4000];
bool visited[4000];

string name[2001];
long hh[2001];
int pos_l[2000];
int pos_r[2000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    // avoid destruction
    unordered_map<long, int> &m1 = *new unordered_map<long, int>;
    unordered_map<long, pair<int, int>> &m2 = *new unordered_map<long, pair<int, int>>;

    for (int i = 0; i < n; ++i) {
        cin >> k[i];

        for (int j = 0; j < k[i]; ++j) {
            cin >> name[m1.size()];

            hh[m1.size()] = hash<string>()(name[m1.size()]);
            h[i] ^= hh[m1.size()];
            m1.insert({hh[m1.size()], m1.size()});
        }
    }

    for (int i = 0; i < m1.size(); ++i) {
        for (int j = i + 1; j < m1.size(); ++j) {
            m2.insert({hh[i] ^ hh[j], {i, j}});
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (abs(k[i] - k[j]) == 1 && m1.find(h[i] ^ h[j]) != m1.end()) {
                if (n_to[i] >= 2 || n_to[j] >= 2) {
                    cout << "IMPOSSIBLE" << endl;

                    return 0;
                }

                n_to[i] += 1;
                n_to[j] += 1;
                to[i] ^= j;
                to[j] ^= i;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (k[i] > 1 && k[j] > 1 && n_to[i] < 2 && n_to[j] < 2 && k[i] == k[j] && m2.find(h[i] ^ h[j]) != m2.end()) {
                n_to[i] += 1;
                n_to[j] += 1;
                to[i] ^= j;
                to[j] ^= i;
            }
        }
    }

    int pos = 1;

    for (int i = 0; i < n; ++i) {
        if (visited[i] || k[i] != 1 || n_to[i] > 1) continue;

        int curr = i;

        pos_l[m1[h[curr]]] = pos++;

        while (true) {
            visited[curr] = true;

            if (!n_to[curr]) break;

            int next = to[curr];

            n_to[next] -= 1;
            to[next] ^= curr;

            if (k[curr] == k[next] - 1) {
                pos_l[m1[h[curr] ^ h[next]]] = pos++;
            } else if (k[curr] == k[next]) {
                pair<int, int> p = m2[h[curr] ^ h[next]];

                if (pos_l[p.first]) {
                    pos_r[p.first] = pos;
                    pos_l[p.second] = pos++;
                } else {
                    pos_r[p.second] = pos;
                    pos_l[p.first] = pos++;
                }
            } else {
                pos_r[m1[h[curr] ^ h[next]]] = pos++;
            }

            curr = next;
        }

        if (k[curr] != 1) {
            cout << "IMPOSSIBLE" << endl;

            return 0;
        }

        pos_r[m1[h[curr]]] = pos++;
    }

    for (int i = 0; i < m1.size(); ++i) {
        if (!visited[i]) {
            cout << "IMPOSSIBLE" << endl;

            return 0;
        }
    }

    for (int i = 0; i < m1.size(); ++i) {
        cout << name[i] << ' ' << pos_l[i] << ' ' << pos_r[i] << endl;
    }

    return 0;
}
