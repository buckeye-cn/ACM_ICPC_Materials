// https://open.kattis.com/problems/froshweek2

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int task[100000];
int quiet[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;

        task[t - 100000] += 1;
    }

    for (int i = 0; i < m; ++i) {
        int l;
        cin >> l;

        quiet[l - 100000] += 1;
    }

    int remain = 0;
    int done = 0;

    for (int i = 99999; i >= 0; --i) {
        remain += quiet[i];

        int delta = min(task[i], remain);

        done += delta;
        remain -= delta;
    }

    cout << done << endl;

    return 0;
}
