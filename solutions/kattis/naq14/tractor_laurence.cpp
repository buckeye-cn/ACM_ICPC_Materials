#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    unsigned N;
    cin >> N;

    for (unsigned i = 0; i < N; i++) {
        unsigned a, b;
        cin >> a >> b;
        a += 1; b += 1;
        if (a > b) swap(a, b);

        unsigned np = 0, x = 1;
        unsigned lb = 0, ub = 64 - __builtin_clzl(b); // most significant bit
        while (x <= a) {
            if ((1<<lb) < x  ) lb++;
            if ((1<<ub) < x+b) ub++;
            unsigned ni = min(min((1<<lb)-x, (1<<ub)-(x+b)), a-x) + 1;
            np += ni * (ub - lb);
            x += ni;
        }
        cout << np << endl;
    }
}
