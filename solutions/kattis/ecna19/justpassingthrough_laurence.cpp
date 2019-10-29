#include <bits/stdc++.h>

using namespace std;

struct {
    int height;
    bool ispass;
} m[500][500];

struct {
    int cc;
    bool valid;
} t[500][500][11];

auto& gett(int i, int j, int k) {
    return t[i][j][k];
}

void sett(int i, int j, int k, int cc) {
    auto& cell = gett(i, j, k);
    if (cell.valid)
        cell.cc = min(cell.cc, cc);
    else {
        cell.valid = true;
        cell.cc = cc;
    }
}

struct key_hash {
    size_t operator()(const array<int, 2>& k) const {
        return (((uint64_t)k[0]) << 32) | (uint64_t)k[1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int R, C, N;
    cin >> R >> C >> N;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> m[i][j].height;
        }
    }
    for (int i = 1; i < R-1; i++) {
        for (int j = 1; j < C-1; j++) {
            auto& self = m[i][j].height;
            m[i][j].ispass = self >= 0
                && m[i-1][j].height >= 0
                && m[i+1][j].height >= 0
                && m[i][j-1].height >= 0
                && m[i][j+1].height >= 0
                && self < m[i-1][j].height
                && self < m[i+1][j].height
                && self > m[i][j-1].height
                && self > m[i][j+1].height;
        }
    }

    unordered_set<array<int, 2>, key_hash> s1, s2;

#define SETT(I, J, K, CC) if (m[I][J].height >= 0) { sett(I, J, K, m[I][J].height + CC); s2.insert(array<int, 2> {{ I, K }}); }

    for (int i = 0; i < R; i++) {
        SETT(i, 0, 0, 0);
    }

    for (int j = 0; j < C-1; j++) {
        s1.clear();
        s1.swap(s2);
        for (auto const& p : s1) {
            auto i = p[0], k = p[1];
            auto& cell = gett(i,j,k);

#define SETTT(I, J, K) SETT(I, J, K, cell.cc)

            if (!m[i][j].ispass) {
                SETTT(i, j+1, k);
                if (i > 0)
                    SETTT(i-1, j+1, k);
                if (i < R-1)
                    SETTT(i+1, j+1, k);
            } else if (k < N) {
                SETTT(i, j+1, k+1);
                if (i > 0)
                    SETTT(i-1, j+1, k+1);
                if (i < R-1)
                    SETTT(i+1, j+1, k+1);
            }
        }
    }

    //for (int k = 0; k <= N; k++) {
    //    for (int i = 0; i < R; i++) {
    //        for (int j = 0; j < C; j++) {
    //            cout << gett(i,j,k).cc << '\t';
    //        }
    //        cout << '\n';
    //    }
    //    cout << '\n';
    //}

    int mincc = INT_MAX;
    for (int i = 0; i < R; i++) {
        auto const& cell = gett(i, C-1, N);
        if (cell.valid)
            mincc = min(mincc, cell.cc);
    }
    if (mincc < INT_MAX)
        cout << mincc << endl;
    else
        cout << "impossible" << endl;
}
