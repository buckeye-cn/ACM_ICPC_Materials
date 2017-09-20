/*
ID: hu.13381
PROG: wormhole
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int cp[24];
bool l[24];
int tot;

void rec() { // can use dp here
    for (int i = 0; i < 24; ++i) cout << cp[i] << (l[i] ? 'L' : ' ') << ' '; cout << endl;
    for (int i = 0; i < 24; ++i) {
        if (!cp[i]) continue;
        if (l[i]) return;
        cp[i] -= 1;

        // same line
        for (int cut = 1; cut < (l[i] ? cp[i] - 1 : cp[i]); ++cut) {
            for (int j = 12; j < 24; ++j) {
                if (cp[j] || l[j]) continue;
                cp[i] -= 1;
                cp[i] -= cut;
                cp[j] += cut;
                l[j] = true;

                cout << 'a' << i << ':' << j << ' ';
                rec();

                cp[i] += 1;
                cp[i] += cut;
                cp[j] -= cut;
                l[j] = false;
                break;
            }
        }
        // different line
        for (int j = i + 1; j < 24; ++j) {
            for (int cut = 0; cut < cp[j]; ++cut) {
                if (!cp[j]) continue;
                cp[j] -= 1;
                cp[j] -= cut;
                cp[i] += cut;
                int n = cp[j];
                if (l[j]) cp[j] -= n;
                if (l[j]) cp[i] += n;

                cout << 'b' << i << ':' << j << ' ';
                rec();

                cp[j] += 1;
                cp[j] += cut;
                cp[i] -= cut;
                if (l[j]) cp[j] += n;
                if (l[j]) cp[i] -= n;
            }
        }

        cp[i] += 1;
        return;
    }
    ++tot;
}

int main() {
    ofstream fout ("wormhole.out");
    ifstream fin ("wormhole.in");

    int c;
    fin >> c;

    map<int, set<int>> grid;
    for (int xx = 0; xx < c; ++xx) {
        int x, y;
        fin >> x >> y;
        if (grid.find(y) != grid.end()) {
            grid[y].insert(x);
        } else {
            grid[y] = {x};
        }
    }

    int y = 0;
    for (auto i: grid) {
        cp[y] = i.second.size();
        y += 1;
    }

    rec();

    int xxx[] = {0, 0, 1, 0, 1*3, 0, 1*3*5, 0, 1*3*5*7, 0, 1*3*5*7*9, 0, 1*3*5*7*9*11};

    cout << c << ' ' << tot;
    fout << xxx[c] - tot << endl;

    return 0;
}
