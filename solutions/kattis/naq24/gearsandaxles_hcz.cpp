// https://open.kattis.com/problems/gearsandaxles

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

pair<int, int> sc[100001];
int v[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> sc[i].first >> sc[i].second;
    }

    sc[n].first = 1000000;
    sort(sc, sc + n);

    int vcount = 0;
    int prev = 0;
    double result = 0;

    for (int i = 0; i <= n; ++i) {
        if (i && sc[i].first != sc[i - 1].first) {
            for (int i = 0; i < vcount / 2; ++i) {
                result -= log(v[i]);
                result += log(v[vcount - 1 - i]);
            }

            vcount = 0;
        }

        v[vcount++] = sc[i].second;
    }

    cout << result << endl;

    return 0;
}
