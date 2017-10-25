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
vector<int> x2018[2018][999];
vector<int> x1680[1680][1118];
vector<int> y1680[1118][1680];
vector<int> y2018[999][2018];

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

        x2018[xx % 2018][yy % 999].push_back(i);
        x1680[xx % 1680][yy % 1118].push_back(i);
        y1680[xx % 1118][yy % 1680].push_back(i);
        y2018[xx % 999][yy % 2018].push_back(i);
    }

    long count = 0;

    for (int p = 0; p < 2018; ++p)
    for (int q = 0; q < 999; ++q)
    for (int i: x2018[p][q])
    for (int j: x2018[p][q]) {
        if (x[i] + 2018 == x[j] && y[i] == y[j]) {
            count += 1;
        }
    }

    for (int p = 0; p < 1680; ++p)
    for (int q = 0; q < 1118; ++q)
    for (int i: x1680[p][q])
    for (int j: x1680[p][q]) {
        if (x[i] + 1680 == x[j] && y[i] + 1118 == y[j]) {
            count += 1;
        } else if (x[i] + 1680 == x[j] && y[i] - 1118 == y[j]) {
            count += 1;
        }
    }

    for (int p = 0; p < 1118; ++p)
    for (int q = 0; q < 1680; ++q)
    for (int i: y1680[p][q])
    for (int j: y1680[p][q]) {
        if (x[i] + 1118 == x[j] && y[i] + 1680 == y[j]) {
            count += 1;
        } else if (x[i] + 1118 == x[j] && y[i] - 1680 == y[j]) {
            count += 1;
        }
    }

    for (int p = 0; p < 999; ++p)
    for (int q = 0; q < 2018; ++q)
    for (int i: y2018[p][q])
    for (int j: y2018[p][q]) {
        if (x[i] == x[j] && y[i] + 2018 == y[j]) {
            count += 1;
        }
    }

    cout << count << endl;

    return 0;
}
