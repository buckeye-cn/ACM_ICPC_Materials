/*
ID: hu.13381
PROG: castle
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

int m, n;
unsigned castle[100][100];
bool visited[100][100];
int group[100][100];
int size[10000];
int tot_g;

int visit(int x, int y, int gid) {
    if (visited[x][y]) {
        return 0;
    }
    visited[x][y] = true;
    group[x][y] = gid;

    int sum = 1;
    if (x > 0 && !(castle[x][y] & 1)) sum += visit(x - 1, y, gid);
    if (y > 0 && !(castle[x][y] & 2)) sum += visit(x, y - 1, gid);
    if (x < m - 1 && !(castle[x][y] & 4)) sum += visit(x + 1, y, gid);
    if (y < n - 1 && !(castle[x][y] & 8)) sum += visit(x, y + 1, gid);

    return sum;
}

int main() {
    ofstream fout ("castle.out");
    ifstream fin ("castle.in");

    fin >> m >> n;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            int x;
            fin >> x;
            castle[i][j] = x;
        }
    }

    int maxsize = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            if (!visited[i][j]) {
                size[tot_g] = visit(i, j, tot_g);
                if (size[tot_g] > maxsize) {
                    maxsize = size[tot_g];
                }
                tot_g += 1;
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            cout << group[i][j] << ' ' << castle[i][j] << '\t';
        }
        cout << endl;
    }

    fout << tot_g << endl;
    fout << maxsize << endl;

    int maxsize2 = 0;
    int maxx, maxy;
    char maxd = '?';
    for (int i = m - 1; i >= 0; --i) {
        for (int j = 0; j < n; ++j) {
            // E
            if (i + 1 < m && group[i][j] != group[i + 1][j] && (castle[i][j] & 4)) {
                if (maxsize2 <= size[group[i][j]] + size[group[i + 1][j]]) {
                    maxsize2 = size[group[i][j]] + size[group[i + 1][j]];
                    maxx = i;
                    maxy = j;
                    maxd = 'E';
                }
            }
            // N
            if (j > 0 && group[i][j] != group[i][j - 1] && (castle[i][j] & 2)) {
                if (maxsize2 <= size[group[i][j]] + size[group[i][j - 1]]) {
                    maxsize2 = size[group[i][j]] + size[group[i][j - 1]];
                    maxx = i;
                    maxy = j;
                    maxd = 'N';
                }
            }
        }
    }

    fout << maxsize2 << endl;
    fout<< (maxy + 1) << ' ' << (maxx + 1) << ' ' << maxd << endl;

    return 0;
}
