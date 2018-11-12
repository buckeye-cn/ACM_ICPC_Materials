// https://open.kattis.com/problems/punctiliouscruciverbalist

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

string s[50];
int clue[50][50];
int len_i[50][50];
int len_j[50][50];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int r, c;
    cin >> r >> c;

    for (int i = 0; i < r; ++i) {
        cin >> s[i];
    }

    int clue_tot = 0;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (s[i][j] != '#') {
                if (!i || s[i - 1][j] == '#') {
                    for (int ii = i; ii < r && s[ii][j] != '#'; ++ii) {
                        len_i[i][j] += 1;
                    }
                }

                if (!j || s[i][j - 1] == '#') {
                    for (int jj = j; jj < c && s[i][jj] != '#'; ++jj) {
                        len_j[i][j] += 1;
                    }
                }

                if (len_i[i][j] || len_j[i][j]) {
                    clue[i][j] = clue_tot++;
                }
            }
        }
    }

    while (true) {
        int best_top = -1;
        int best_base = 1;
        int best_clue;
        char best_mode;
        int best_i;
        int best_j;

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (len_j[i][j]) {
                    int top = 0;
                    int base = len_j[i][j] * (len_j[i][j] + 1) / 2;

                    for (int jj = 0; jj < len_j[i][j]; ++jj) {
                        if (s[i][j + jj] != '.') {
                            top += len_j[i][j] - jj;
                        }
                    }

                    if (top == base) {
                        len_j[i][j] = 0;
                    } else if (top * best_base > best_top * base) {
                        best_top = top;
                        best_base = base;
                        best_clue = clue[i][j];
                        best_mode = 'A';
                        best_i = i;
                        best_j = j;
                    }
                }
            }
        }

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (len_i[i][j]) {
                    int top = 0;
                    int base = len_i[i][j] * (len_i[i][j] + 1) / 2;

                    for (int ii = 0; ii < len_i[i][j]; ++ii) {
                        if (s[i + ii][j] != '.') {
                            top += len_i[i][j] - ii;
                        }
                    }

                    if (top == base) {
                        len_i[i][j] = 0;
                    } else if (top * best_base > best_top * base) {
                        best_top = top;
                        best_base = base;
                        best_clue = clue[i][j];
                        best_mode = 'D';
                        best_i = i;
                        best_j = j;
                    }
                }
            }
        }

        if (best_top < 0) {
            return 0;
        }

        if (best_mode == 'D') {
            for (int ii = 0; ii < len_i[best_i][best_j]; ++ii) {
                s[best_i + ii][best_j] = 'X';
            }
        } else {
            for (int jj = 0; jj < len_j[best_i][best_j]; ++jj) {
                s[best_i][best_j + jj] = 'X';
            }
        }

        // for (int i = 0; i < r; ++i) {
        //     for (int j = 0; j < c; ++j) {
        //         cerr << s[i][j];
        //     }
        //     cerr << endl;
        // }

        cout << best_clue + 1 << best_mode << endl;
    }
}
