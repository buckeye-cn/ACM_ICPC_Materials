#include <cmath>
#include <iostream>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, unsigned> unitsr = {};
    while (true) {
        unitsr.clear();

        unsigned n;
        cin >> n;
        if (n == 0) break;

        string units[10] = {};
        double graph[10][10] = {};

        for (unsigned i = 0; i < n; i++) {
            cin >> units[i];
            unitsr[units[i]] = i;
            graph[i][i] = 1.0;
        }

        for (unsigned i = 0; i < (n-1); i++) {
            string u1, u2;
            char _;
            double n;
            cin >> u1 >> _ >> n >> u2;
            unsigned iu1 = unitsr[u1], iu2 = unitsr[u2];
            graph[iu1][iu2] = n;
            graph[iu2][iu1] = 1.0 / n;
        }

        unsigned max_i = 0; double _max = 0;
        for (unsigned k = 0; k < n; k++) {
            for (unsigned i = 0; i < n; i++) {
                for (unsigned j = 0; j < n; j++) {
                    if (graph[i][j] == 0.0 && graph[i][k] != 0.0 && graph[k][j] != 0.0)
                        graph[i][j] = graph[i][k] * graph[k][j];
                    if (graph[i][j] > _max) {
                        _max = graph[i][j];
                        max_i = i;
                    }
                }
            }
        }

        unsigned cur_i = max_i;
        cout << "1" << units[max_i];
        for (unsigned _i = 0; _i < (n-1); _i++) {
            unsigned min_j = 0;
            double _min = 1e32;
            for (unsigned j = 0; j < n; j++) {
                if (1.0 < graph[cur_i][j] && graph[cur_i][j] < _min) {
                    min_j = j;
                    _min = graph[cur_i][j];
                }
            }
            cur_i = min_j;
            cout << " = " << (unsigned)round(graph[max_i][min_j]) << units[cur_i];
        }
        cout << endl;
    }
}
