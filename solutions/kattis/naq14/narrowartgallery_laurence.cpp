#include <iostream>
#include <algorithm>

using namespace std;

unsigned N, K, tot;
unsigned ROOMS[202][2] = {};
uint64_t table[202][202][3] = {};

uint64_t dp(unsigned i, unsigned k, unsigned l) {
    if (k == 0)
        return 0;
    if (i >= N)
        return 1e9;
    if (table[i][k][l] == 0)
        table[i][k][l] = min(dp(i+1, k, 0), (l == 0) ? min(dp(i+1, k-1, 1)+ROOMS[i][0], dp(i+1, k-1, 2)+ROOMS[i][1]) : (l == 1) ? dp(i+1, k-1, 1)+ROOMS[i][0] : (l == 2) ? dp(i+1, k-1, 2)+ROOMS[i][1] : (uint64_t)1e9) | 0x80000000;
    return table[i][k][l] & 0x7fffffff;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> N >> K;

    for (unsigned i = 0; i < N; i++) {
        cin >> ROOMS[i][0] >> ROOMS[i][1];
        tot += ROOMS[i][0] +  ROOMS[i][1];
    }

    cout << tot - dp(0, K, 0) << endl;
}
