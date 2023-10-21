// https://open.kattis.com/problems/borg

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

template <long N>
struct Prim {
    struct Edge {
        long to, len;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long len) {
        edges.push_back({to, len});
        outs[from].push_back(edges.size() - 1);
        edges.push_back({from, len});
        outs[to].push_back(edges.size() - 1);
    }

    long dist[N];
    long route[N];

    long solve() {
        set<pair<long, long>> q;

        for (long i = 0; i < N; ++i) {
            dist[i] = 1l << 60;
            q.insert({dist[i], i});
        }

        while (!q.empty()) {
            pair<long, long> i = *q.begin();
            q.erase(i);

            if (i.first == 1l << 60) {
                dist[i.second] = 0;
            }

            for (long j = 0; j < outs[i.second].size(); ++j) {
                Edge &e = edges[outs[i.second][j]];

                if (dist[e.to] > e.len) {
                    if (q.find({dist[e.to], e.to}) != q.end()) {
                        q.erase({dist[e.to], e.to});
                        dist[e.to] = e.len;
                        route[e.to] = i.second;
                        q.insert({dist[e.to], e.to});
                    }
                }
            }
        }

        long result = 0;

        for (long i = 0; i < N; ++i) {
            result += dist[i];
        }

        return result;
    }
};

Prim<101> prim[50];

int x, y;
char mapdata[60][60];

int q_x[3600][3600];
int q_y[3600][3600];
int q_tot[3600];
int dist[60][60][60][60];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> y >> x;

        cin.get();

        for (int j = 0; j < x; ++j) {
            cin.getline(mapdata[j], y + 1);
        }

        for (int j = 0; j < x; ++j) {
            for (int k = 0; k < y; ++k) {
                if (mapdata[j][k] != 'A' && mapdata[j][k] != 'S') {
                    continue;
                }

                for (int l = 0; l < x; ++l) {
                    for (int m = 0; m < y; ++m) {
                        dist[j][k][l][m] = -1;
                    }
                }

                q_x[0][0] = j;
                q_y[0][0] = k;
                q_tot[0] = 1;

                for (int l = 0; q_tot[l]; ++l) {
                    q_tot[l + 1] = 0;

                    for (int m = 0; m < q_tot[l]; ++m) {
                        auto add = [&](int xx, int yy) {
                            if (mapdata[xx][yy] == '#') return;
                            if (dist[j][k][xx][yy] != -1) return;

                            dist[j][k][xx][yy] = l + 1;

                            q_x[l + 1][q_tot[l + 1]] = xx;
                            q_y[l + 1][q_tot[l + 1]] = yy;
                            q_tot[l + 1] += 1;
                        };

                        add(q_x[l][m] - 1, q_y[l][m]);
                        add(q_x[l][m] + 1, q_y[l][m]);
                        add(q_x[l][m], q_y[l][m] - 1);
                        add(q_x[l][m], q_y[l][m] + 1);
                    }
                }
            }
        }

        int i1 = 0;
        for (int j = 0; j < x; ++j) {
            for (int k = 0; k < y; ++k) {
                if (mapdata[j][k] != 'A' && mapdata[j][k] != 'S') {
                    continue;
                }

                int i2 = 0;
                for (int l = 0; l < x; ++l) {
                    for (int m = 0; m < y; ++m) {
                        if (mapdata[l][m] != 'A' && mapdata[l][m] != 'S') {
                            continue;
                        }

                        if (i1 < i2) {
                            prim[i].add(i1, i2, dist[j][k][l][m]);
                        }

                        i2 += 1;
                    }
                }

                i1 += 1;
            }
        }

        cout << prim[i].solve() << endl;
    }

    return 0;
}
