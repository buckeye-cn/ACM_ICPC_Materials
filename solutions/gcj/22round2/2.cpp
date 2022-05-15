#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

long circle[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (long r = 1; r <= 100000; ++r) {
        long x = floor(r / sqrt(2));
        long y = round(sqrt(sqr(r) - sqr(x)));

        circle[r] += x * 8 + 4 - (x == y) * 4;

        x = ceil(r / sqrt(2));
        y = round(sqrt(sqr(r) - sqr(x)));

        circle[r] += (x == y) * 4;
    }

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        long r;
        cin >> r;

        long s1 = 1;

        for (long x = 1; x <= r; ++x) {
            s1 += ceil(sqrt(sqr(r + 0.5) - sqr(x))) * 4;
        }

        long s2 = 1;

        for (long rr = 1; rr <= r; ++rr) {
            s2 += circle[rr];
        }

        cout << s1 - s2 << endl;
    }

    return 0;
}
