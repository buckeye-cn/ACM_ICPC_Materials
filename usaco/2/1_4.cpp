/*
ID: hu.13381
PROG: holstein
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ofstream fout ("holstein.out");
    ifstream fin ("holstein.in");

    int v;
    int vt[100];
    int g;
    int gt[100][100];

    fin >> v;
    for (int i = 0; i < v; ++i) {
        fin >> vt[i];
    }
    fin >> g;
    for (int j = 0; j < g; ++j) {
        for (int i = 0; i < v; ++i) {
            fin >> gt[j][i];
        }
    }

    vector<tuple<vector<int>, int, int>> cache;
    {
        vector<int> t;
        for (int i = 0; i < v; ++i) t.push_back(0);
        cache.push_back(tuple<vector<int>, int, int>{move(t), 0, 0});
    }
    for (int k = 1; k <= g; ++k) {
        vector<tuple<vector<int>, int, int>> new_cache;
        for (auto &c: cache) {
            for (int j = get<2>(c); j < g; ++j) {
                vector<int> t;
                for (int i = 0; i < v; ++i) t.push_back(get<0>(c)[i] + gt[j][i]);
                new_cache.push_back(tuple<vector<int>, int, int>{move(t), get<1>(c) | (1 << j), j + 1});
            }
        }
        cache.clear();
        for (auto &c: new_cache) {
            bool fin = true;
            for (int i = 0; i < v; ++i) if (get<0>(c)[i] < vt[i]) {
                fin = false;
                break;
            }
            if (fin) {
                fout << k;
                for (int j = 0; j < g; ++j) {
                    if (get<1>(c) & (1 << j)) {
                        fout << ' ' << (j + 1);
                    }
                }
                fout << endl;

                return 0;
            } else {
                bool ok = true;
                // for (auto &c1: new_cache) {
                //     bool k = false;
                //     for (int i = 0; i < v; ++i) if (get<0>(c1)[i] <= get<0>(c)[i]) {
                //         k = true;
                //         break;
                //     }
                //     if (!k) {
                //         ok = false;
                //         break;
                //     }
                // }
                if (ok) {
                    cache.push_back(c);
                }
            }
        }
    }

    return 0;
}
