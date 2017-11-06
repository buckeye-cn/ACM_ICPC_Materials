#include <algorithm>
#include <iostream>

using namespace std;

int32_t NHB[2];
int32_t SIZE[2][100] = {};
int32_t SUM[2] = {};

int32_t NP[2][100000][100] = {};

constexpr int32_t inf = 1e8;

template<unsigned hb>
int32_t dp(int32_t x, int32_t i) {
    while (SIZE[hb][i] > x)
        i--;

    if (i < 0)
        return inf;

    if (NP[hb][x][i] > 0)
        return NP[hb][x][i];

    int32_t np1 = dp<hb>(x, i-1);
    int32_t _x = x-SIZE[hb][i];
    int32_t np2 = (_x == 0) ? 1 : dp<hb>(_x, i-1) + 1;

    int32_t np = min(np1, np2);
    NP[hb][x][i] = np;

    return np;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (unsigned hb = 0; hb < 2; hb++) {
        cin >> NHB[hb];
        for (int32_t j = 0; j < NHB[hb]; j++) {
            cin >> SIZE[hb][j];
            SUM[hb] += SIZE[hb][j];
        }
        sort(begin(SIZE[hb]), begin(SIZE[hb])+NHB[hb]);
    }

    int32_t min_tot = inf;

    for (int32_t x = 1; x <= min(SUM[0], SUM[1]); x++) {
        int32_t np1 = dp<0>(x, NHB[0]-1);
        int32_t np2 = dp<1>(x, NHB[1]-1);
        min_tot = min(min_tot, np1 + np2);
    }

    if (min_tot < inf) {
        cout << min_tot << "\n";
    } else {
        cout << "impossible\n";
    }
}
