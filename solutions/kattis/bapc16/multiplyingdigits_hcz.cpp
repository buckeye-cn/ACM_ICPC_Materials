// https://open.kattis.com/problems/multiplyingdigits

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

long b;
long bound;
int digit_n;
long digit[10000];
unordered_map<long, long> m;

long dfs(long n) {
    if (n < b) {
        return n;
    }

    long &best = m[n];

    if (!best) {
        best = 1l << 63;

        for (int i = 0; i < digit_n; ++i) {
            if (n % digit[i] == 0) {
                long pbest = dfs(n / digit[i]);

                if (pbest > 0 && pbest <= bound && pbest * b < best - digit[i]) {
                    best = pbest * b + digit[i];
                }
            }
        }
    }

    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long n;
    cin >> b >> n;

    bound = ~(1l << 63) / b;

    for (long i = b - 1; i * i >= b; --i) {
        if (n % i == 0) {
            digit[digit_n] = i;
            digit_n += 1;
        }
    }

    long best = dfs(n);

    if (best > 0) {
        cout << best << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
