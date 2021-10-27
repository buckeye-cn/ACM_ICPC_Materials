// https://open.kattis.com/problems/speedlimit

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        int n;
        cin >> n;

        if (n == -1) {
            return 0;
        }

        int len = 0;
        int now = 0;

        for (int i = 0; i < n; ++i) {
            int s, t;
            cin >> s >> t;

            len += (t - now) * s;
            now = t;
        }

        cout << len << " miles" << endl;
    }
}
