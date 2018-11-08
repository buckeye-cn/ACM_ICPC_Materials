#include <bits/stdc++.h>
#include "edmondskarp.hpp"

using namespace std;

int N, S, F, C, SO, TO;

unordered_map<string, int> _N2I;
int N2I(string& n) {
    if (_N2I.count(n) == 0) {
        _N2I.emplace(n, _N2I.size()); // vs _N2I[n] = _N2I.size()-1;
    }
    return _N2I[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> N >> S >> F >> C;
    SO = N + C * 2;
    TO = SO + 1;

    EdmondsKarp<long> ed(N + C * 2 + 2);

    _N2I.reserve(N);
    for (int i = 0; i < S; i++) {
        string n;
        cin >> n;
        ed.add(SO, N2I(n), 1);
    }
    for (int i = 0; i < F; i++) {
        string n;
        cin >> n;
        ed.add(N2I(n), TO, 1);
    }
    for (int ci = 0; ci < C; ci++) {
        int ffi = N + ci * 2, fi = ffi + 1;
        ed.add(ffi, fi, 1);
        int nco;
        cin >> nco;
        for (int j = 0; j < nco; j++) {
            string n;
            cin >> n;
            ed.add(N2I(n), ffi, 1);
            ed.add(fi, N2I(n), 1);
        }
    }
    cout << ed.solve(SO, TO) << endl;
}
