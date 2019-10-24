// https://open.kattis.com/problems/sound

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int a[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m, c;
    cin >> n >> m >> c;

    bool none = true;

    multiset<int> s;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];

        if (i >= m) {
            s.erase(s.find(a[i - m]));
        }

        s.insert(a[i]);

        if (i >= m - 1 && *s.rbegin() - *s.begin() <= c) {
            printf("%d\n", i - m + 2);

            none = false;
        }
    }

    if (none) {
        printf("NONE\n");
    }

    return 0;
}
