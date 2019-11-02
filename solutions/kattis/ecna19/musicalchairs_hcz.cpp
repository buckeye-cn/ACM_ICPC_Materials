// https://open.kattis.com/problems/musicalchairs

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

pair<int, int> k[10000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> k[i].first;
        k[i].second = i + 1;
    }

    int pos = 0;

    for (int i = n; i > 1; --i) {
        pos = (pos + k[pos % i].first - 1) % i;

        memmove(k + pos, k + pos + 1, (i - pos - 1) * sizeof(pair<int, int>));
    }

    cout << k[0].second << endl;

    return 0;
}
