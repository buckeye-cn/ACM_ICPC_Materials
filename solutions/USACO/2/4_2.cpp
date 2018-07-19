/*
ID: hu.13381
PROG: maze1
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

int main() {
    ofstream fout ("maze1.out");
    ifstream fin ("maze1.in");

    int dist[120][120];
    bool dec_i[120][120];
    bool dec_j[120][120];

    int w, h;
    fin >> w >> h;

    string ss;
    getline(fin, ss); // flush

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            dist[i][j] = 120 * 120;
        }
    }

    for (int i = 0; i < h + 1; ++i) {
        string s;
        getline(fin, s);
        for (int j = 0; j < w; ++j) {
            dec_i[i][j] = (s[1 + 2 * j] == ' ');
        }
        if (i == h) break;
        getline(fin, s);
        for (int j = 0; j < w + 1; ++j) {
            dec_j[i][j] = (s[2 * j] == ' ');
        }
    }

    bool loop = true;
    while (loop) { // can be optimized: only scan nodes near updated nodes
        loop = false;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int t = dist[i][j];
                if (dec_i[i][j]) {
                    if (i == 0) {
                        t = 1;
                    } else {
                        if (t > dist[i - 1][j] + 1) t = dist[i - 1][j] + 1;
                    }
                }
                if (dec_j[i][j]) {
                    if (j == 0) {
                        t = 1;
                    } else {
                        if (t > dist[i][j - 1] + 1) t = dist[i][j - 1] + 1;
                    }
                }
                if (dec_i[i + 1][j]) {
                    if (i == h - 1) {
                        t = 1;
                    } else {
                        if (t > dist[i + 1][j] + 1) t = dist[i + 1][j] + 1;
                    }
                }
                if (dec_j[i][j + 1]) {
                    if (j == w - 1) {
                        t = 1;
                    } else {
                        if (t > dist[i][j + 1] + 1) t = dist[i][j + 1] + 1;
                    }
                }
                if (t != dist[i][j]) {
                    loop = true;
                    dist[i][j] = t;
                }
            }
        }
        // for (int i = 0; i < h; ++i) {
        //     for (int j = 0; j < w; ++j) {
        //         cerr << dist[i][j] << '\t';
        //     }
        //     cerr << endl;
        // }
        // cerr << endl;
    }

    int max = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (dist[i][j] > max) {
                max = dist[i][j];
            }
        }
    }

    fout << max << endl;

    return 0;
}
