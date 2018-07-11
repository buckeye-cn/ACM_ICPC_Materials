#include <cmath>
#include <iostream>

#include "dijkstra.hpp"

using namespace std;

typedef float F;

constexpr F RUN_SPEED = 5.;  // 5 m/s
constexpr F LNCH_DIST = 50.; // 50 m
constexpr F LNCH_TIME = 2.;  // 2 s

struct Pos {
    F x, y;

    F operator|(Pos o) const {
        return hypot(x - o.x, y - o.y);
    }
};

Pos CUR, DST, CNN_POS[103];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    short N;

    cin >> CUR.x >> CUR.y >> DST.x >> DST.y;
    cin >> N;
    for (short i = 0; i < N; i++)
        cin >> CNN_POS[i].x >> CNN_POS[i].y;
    CNN_POS[N] = DST;

    Dijkstra<F> D(N+2);

    for (short i = 0; i <= N; i++) {
        for (short j = i + 1; j <= N; j++) {
            F d = CNN_POS[i] | CNN_POS[j];
            F t1 = abs(d - LNCH_DIST) / RUN_SPEED + LNCH_TIME;
            F t2 = d / RUN_SPEED;
            D.add_u(i, j, min(t1, t2));
        }
        D.add(N+1, i, (CUR | CNN_POS[i]) / RUN_SPEED);
    }

    cout << D.solve(N+1, N) << '\n';
}
