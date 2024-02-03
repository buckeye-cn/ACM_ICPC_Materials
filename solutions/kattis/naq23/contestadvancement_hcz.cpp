// https://open.kattis.com/problems/contestadvancement

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int t[100000];
int s[100000];
int nn[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, k, c;
    cin >> n >> k >> c;
    int kk = 0;

    for (int i = 0; i < n; ++i) {
        cin >> t[i] >> s[i];

        if (nn[s[i]] < c && kk < k) {
            nn[s[i]] += 1;
            kk += 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (nn[s[i]]) {
            nn[s[i]] -= 1;
            cout << t[i] << endl;
        } else if (kk < k) {
            kk += 1;
            cout << t[i] << endl;
        }
    }

    return 0;
}
