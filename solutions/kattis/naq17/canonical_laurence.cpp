#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

static int N;
static array<int32_t, 100> cs = {};

inline int32_t greedy(int32_t x) {
    int32_t c = 0;
    int32_t i = N-1;
    int32_t t = 0;
    while (1) {
        int32_t d = x - t;

        while (i > 0 && cs[i] > d)
            i--;

        if (i == 0) {
            return c + d;
        } else {
            c += 1;
            t += cs[i];
        }
    }
    return c;
}

static array<int32_t, 2*1000000> nc = {};

int32_t dp(int32_t x, int32_t i) {
    if (x == 0)
        return 0;

    if (nc[x] > 0)
        return nc[x];

    while (x < cs[i])
        i--;

    if (i == 0)
        return x;

    int32_t n1 = dp(x - cs[i], i) + 1;
    int32_t n2 = dp(x, i - 1);
    int32_t n = min(n1, n2);
    nc[x] = n;
    return n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> N;

    for (int i = 0; i < N; i++) {
        int32_t c;
        cin >> c;
        cs[i] = c;
    }

    for (int32_t x = 1; x < (cs[N-1]+cs[N-2]); x++) {
        int32_t n1 = greedy(x);
        int32_t n2 = dp(x, N-1);
        if (n1 != n2) {
            cout << "non-canonical\n";
            return 0;
        }
    }
    cout << "canonical\n";
}
