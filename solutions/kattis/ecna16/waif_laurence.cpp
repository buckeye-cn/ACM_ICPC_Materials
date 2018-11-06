#include <bits/stdc++.h>
#include "edmondskarp.hpp"

using namespace std;

int C, T, P, SO, TO;

#define CI(ci) (ci-1)
#define TI(ti) (ti+C-1)
#define PI(pi) (pi+C+T-1)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> C >> T >> P;
    SO = C+T+P;
    TO = SO+1;

    EdmondsKarp<long> ed(TO+1);

    for (int ci = 1; ci <= C; ci++) {
        int k; cin >> k;
        for (int _k = 0; _k < k; _k++) {
            int ti; cin >> ti;
            ed.add(TI(ti), CI(ci), 1);
        }
        ed.add(CI(ci), TO, 1);
    }
    static bool tvd[103];
    for (int pi = 1; pi <= P; pi++) {
        int l; cin >> l;
        for (int _l = 0; _l < l; _l++) {
            int ti; cin >> ti;
            tvd[ti]+=1;
            ed.add(PI(pi), TI(ti), 1);
        }
        int r; cin >> r;
        ed.add(SO, PI(pi), r);
    }
    for (int ti = 1; ti <= T; ti++)
        if (!tvd[ti])
            ed.add(SO, TI(ti), 1);

    cout<<ed.solve(SO,TO)<<endl;
}
