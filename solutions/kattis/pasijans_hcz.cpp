// https://open.kattis.com/problems/pasijans

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int n;
int tot[1024];
int data[1024][1024];
int cache[1024][1024][2][32];

struct Comp {
    bool operator() (int x, int y) const {
        if (tot[x] > tot[y]) {
            size_t diff = tot[x] - tot[y];

            if (cache[x][y][false][(diff >> 5) & 31] & 1 << (diff & 31)) {
                return false;
            }
            if (cache[x][y][true][(diff >> 5) & 31] & 1 << (diff & 31)) {
                return true;
            }
        } else {
            size_t diff = tot[y] - tot[x];

            if (cache[y][x][false][(diff >> 5) & 31] & 1 << (diff & 31)) {
                return true;
            }
            if (cache[y][x][true][(diff >> 5) & 31] & 1 << (diff & 31)) {
                return false;
            }
        }

        int i = tot[x] - 1;
        int j = tot[y] - 1;

        bool result;

        while (true) {
            if (j < 0) {
                result = true;
                break;
            }
            if (i < 0) {
                result = false;
                break;
            }
            if (data[x][i] < data[y][j]) {
                result = true;
                break;
            }
            if (data[x][i] > data[y][j]) {
                result = false;
                break;
            }

            --i;
            --j;
        }

        if (i < 0 || j < 0) {
            if (tot[x] > tot[y]) {
                size_t diff = tot[x] - tot[y];

                cache[x][y][result][(diff >> 5) & 31] |= 1 << (diff & 31);
            } else {
                size_t diff = tot[y] - tot[x];

                cache[y][x][!result][(diff >> 5) & 31] |= 1 << (diff & 31);
            }
        }

        return result;
    }
};

set<int, Comp> compset;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> tot[i];

        for (int j = tot[i] - 1; j >= 0; --j) {
            int item;
            cin >> item;

            data[i][j] = item;
        }

        compset.insert(i);
    }

    bool first = true;
    while (!compset.empty()) {
        if (!first) cout << ' ';
        first = false;

        int i = *compset.begin();
        compset.erase(compset.begin());

        int flag = data[i][tot[i] - 1];
        cout << data[i][tot[i] - 1];
        tot[i] -= 1;

        while (tot[i] && data[i][tot[i] - 1] < flag) {
            cout << ' ' << data[i][tot[i] - 1];
            tot[i] -= 1;
        }

        if (tot[i]) {
            compset.insert(i);
        }
    }

    cout << endl;

    return 0;
}
