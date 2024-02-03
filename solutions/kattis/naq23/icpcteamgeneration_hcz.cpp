// https://open.kattis.com/problems/icpcteamgeneration

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int a[52];
int b[52];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    int res = 0;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i + 1] >> b[i + 1];

        if (a[i - 1] && a[i] && a[i + 1] <= i - 2 && i <= b[i - 1]) {
            res += 1;
            a[i + 1] = 0;
        }
    }

    cout << res << endl;

    return 0;
}
