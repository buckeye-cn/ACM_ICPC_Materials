// https://open.kattis.com/problems/kenken

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n, m, t;
char op;
int r[10];
int c[10];
long pow_n[11] {1};

bool r_used[10][10];
bool c_used[10][10];

int scan_add(int i, int value) {
    if (i == m) {
        return value == t;
    }

    if (value + m - i > t || value + n * (m - i) < t) {
        return 0;
    }

    int rr = r[i];
    int cc = c[i];

    int total = 0;

    if (i == m - 1) {
        return !r_used[rr][t - value] && !c_used[cc][t - value];
    } else {
        for (int k = 1; k <= n; ++k) {
            if (r_used[rr][k]) continue;
            if (c_used[cc][k]) continue;

            r_used[rr][k] = true;
            c_used[cc][k] = true;

            total += scan_add(i + 1, value + k);

            r_used[rr][k] = false;
            c_used[cc][k] = false;
        }
    }

    return total;
}

int scan_mul(int i, int value) {
    if (i == m) {
        return value == t;
    }

    if (value > t || value * pow_n[m - i] < t || t % value) {
        return 0;
    }

    int rr = r[i];
    int cc = c[i];

    int total = 0;

    for (int k = 1; k <= n; ++k) {
        if (r_used[rr][k]) continue;
        if (c_used[cc][k]) continue;

        r_used[rr][k] = true;
        c_used[cc][k] = true;

        total += scan_mul(i + 1, value * k);

        r_used[rr][k] = false;
        c_used[cc][k] = false;
    }

    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m >> t >> op;

    for (int i = 0; i < m; ++i) {
        cin >> r[i] >> c[i];

        pow_n[i + 1] = pow_n[i] * n;
    }

    if (op == '+') {
        cout << scan_add(0, 0) << endl;
    } else if (op == '-') {
        cout << max(n - t, 0) * 2 << endl;
    } else if (op == '*') {
        cout << scan_mul(0, 1) << endl;
    } else if (op == '/') {
        if (t == 1 && (r[0] == r[1] || c[0] == c[1])) {
            cout << 0 << endl;
        } else {
            cout << max(n / t, 0) * 2 << endl;
        }
    }

    return 0;
}
