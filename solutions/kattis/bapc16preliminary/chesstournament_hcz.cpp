// https://open.kattis.com/problems/chesstournament

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int n, m, t;

int id[50000];
int from[250000];
int to[250000];

vector<int> out[50000];

int visited[50000];

int id_get(int i) {
    if (id[i] == i) {
        return i;
    } else {
        return id[i] = id_get(id[i]);
    }
}

bool visit(int i, int iter) {
    if (visited[i]) {
        if (visited[i] == iter) {
            return false;
        }
    } else {
        visited[i] = iter;

        for (int j: out[i]) {
            if (!visit(j, iter)) {
                return false;
            }
        }

        visited[i] = -iter;
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        id[i] = i;
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        char c;

        cin >> a >> c >> b;

        if (c == '=') {
            id[id_get(a)] = id_get(b);
        } else {
            from[t] = a;
            to[t] = b;
            t += 1;
        }
    }

    for (int i = 0; i < t; ++i) {
        out[id_get(from[i])].push_back(id_get(to[i]));
    }

    for (int i = 0, iter = 1; i < n; ++i, ++iter) {
        if (id[i] == i && !visited[i]) {
            if (!visit(i, iter)) {
                cout << "inconsistent" << endl;

                return 0;
            }
        }
    }

    // for (int i = 0; i < n; ++i) {
    //     cerr << i << ' ' << id[i] << ' ' << visited[i] << endl;
    // }

    cout << "consistent" << endl;

    return 0;
}
