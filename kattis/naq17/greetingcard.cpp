// https://open.kattis.com/problems/greetingcard

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define sqr(x) ((x) * (x))

int n;
long x[200000];
long y[200000];
vector<int> *x2018[1009][1009];
vector<int> *x1680[560][559];
vector<int> *x1118[559][560];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        long xx, yy;

        cin >> xx >> yy;
        x[i] = xx;
        y[i] = yy;

        if (!x2018[xx % 1009][yy % 1009])
            x2018[xx % 1009][yy % 1009] = new vector<int>();
        x2018[xx % 1009][yy % 1009]->push_back(i);
        if (!x1680[xx % 560][yy % 559])
            x1680[xx % 560][yy % 559] = new vector<int>();
        x1680[xx % 560][yy % 559]->push_back(i);
        if (!x1118[xx % 559][yy % 560])
            x1118[xx % 559][yy % 560] = new vector<int>();
        x1118[xx % 559][yy % 560]->push_back(i);
    }

    long count = 0;

    for (int p = 0; p < 1009; ++p)
    for (int q = 0; q < 1009; ++q)
    if (x2018[p][q])
    for (int i: *x2018[p][q])
    for (int j: *x2018[p][q]) {
        if (i == j) continue;
        if (x[i] + 2018 == x[j] && y[i] == y[j]) {
            count += 1;
        } else if (x[i] == x[j] && y[i] + 2018 == y[j]) {
            count += 1;
        }
    }

    for (int p = 0; p < 560; ++p)
    for (int q = 0; q < 559; ++q)
    if (x1680[p][q])
    for (int i: *x1680[p][q])
    for (int j: *x1680[p][q]) {
        if (i == j) continue;
        if (x[i] + 1680 == x[j] && y[i] + 1118 == y[j]) {
            count += 1;
        } else if (x[i] + 1680 == x[j] && y[i] - 1118 == y[j]) {
            count += 1;
        }
    }

    for (int p = 0; p < 559; ++p)
    for (int q = 0; q < 560; ++q)
    if (x1118[p][q])
    for (int i: *x1118[p][q])
    for (int j: *x1118[p][q]) {
        if (i == j) continue;
        if (x[i] + 1118 == x[j] && y[i] + 1680 == y[j]) {
            count += 1;
        } else if (x[i] + 1118 == x[j] && y[i] - 1680 == y[j]) {
            count += 1;
        }
    }

    cout << count << endl;

    return 0;
}
