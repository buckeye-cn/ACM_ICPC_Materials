#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(30);

    long D, X;
    cin >> X >> D;

    vector<array<long, 2>> DA;
    DA.resize(D);

    long tot = 0;
    for (long x = 0; x < X; x++) {
        long d, va, vb;
        cin >> d >> va >> vb;
        d -= 1;
        DA[d][0] += va;
        DA[d][1] += vb;
        tot += va + vb;
    }

    long WA = 0, WB = 0;
    for (long d = 0; d < D; d++) {
        if (DA[d][0] > DA[d][1]) {
            long wa = DA[d][0] - (DA[d][0] + DA[d][1]) / 2 - 1;
            long wb = DA[d][1];
            WA += wa;
            WB += wb;
            cout << "A " << wa << ' ' << wb << '\n';
        } else {
            long wa = DA[d][0];
            long wb = DA[d][1] - (DA[d][0] + DA[d][1]) / 2 - 1;
            WA += wa;
            WB += wb;
            cout << "B " << wa << ' ' << wb << '\n';
        }
    }

    cout << abs((double)(WA - WB)) / (double)tot << endl;
}
