// https://open.kattis.com/problems/numble

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char board[22][22];
char v[10];
char new_row[22];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int row, col;
    cin >> row >> col;

    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            cin >> board[i][j];
        }
    }

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        cin >> v[i];

        for (int j = i - 1; j >= 0; --j) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }

    long best = 0;

    for (int d = 0; d < 4; ++d) {
        for (int i = 1; i <= row; ++i) {
            int good = 0;

            for (int j = 1; j <= col; ++j) {
                good |= (board[i][j - 1] >= '0' && board[i][j - 1] <= '9') << j;
                good |= (board[i][j + 1] >= '0' && board[i][j + 1] <= '9') << j;
                good |= (board[i - 1][j] >= '0' && board[i - 1][j] <= '9') << j;
                good |= (board[i + 1][j] >= '0' && board[i + 1][j] <= '9') << j;
            }

            for (int j = 1; j <= col; ++j) {
                good >>= 1;
                if (!good) break;

                if (board[i][j] >= '0' && board[i][j] <= '9') continue;

                for (int mask = 0; mask < 1 << t; ++mask) {
                    memcpy(new_row, board[i], sizeof(board[i]));

                    int k = j;
                    int p = 0;

                    for (; k <= col; ++k) {
                        if (board[i][k] >= '0' && board[i][k] <= '9') continue;

                        while (mask & (1 << p)) {
                            p += 1;
                        }

                        if (p >= t) break;

                        new_row[k] = v[p];
                        p += 1;
                    }

                    if (good >> (k - j) << (k - j) == good) continue;

                    bool inc = true;
                    long val = 0;
                    long jval = (new_row[j] - '0') * (board[i][j] == 't' ? 3 : board[i][j] == 'd' ? 2 : 1);
                    long jmul = board[i][j] == 'T' ? 3 : board[i][j] == 'D' ? 2 : 1;
                    int l = j - 1;
                    int r = j + 1;

                    while (new_row[l] >= '0' && new_row[l] <= '9') {
                        inc &= new_row[l] <= new_row[l + 1];
                        jval += new_row[l] - '0';
                        l -= 1;
                    }

                    while (new_row[r] >= '0' && new_row[r] <= '9') {
                        inc &= new_row[r - 1] <= new_row[r];
                        jval += (new_row[r] - '0') * (board[i][r] == 't' ? 3 : board[i][r] == 'd' ? 2 : 1);
                        jmul *= board[i][r] == 'T' ? 3 : board[i][r] == 'D' ? 2 : 1;
                        r += 1;
                    }

                    if (r - l <= 2) continue;

                    bool ok = inc && jval * jmul % 3 == 0;

                    if (!ok) continue;

                    val += jval * jmul;

                    for (int jj = l + 1; jj <= r - 1; ++jj) {
                        if (board[i][jj] >= '0' && board[i][jj] <= '9') continue;

                        bool inc = true;
                        bool dec = true;
                        long ival = (new_row[jj] - '0') * (board[i][jj] == 't' ? 3 : board[i][jj] == 'd' ? 2 : 1);
                        long imul = board[i][jj] == 'T' ? 3 : board[i][jj] == 'D' ? 2 : 1;
                        int t = i - 1;
                        int b = i + 1;

                        int last = new_row[jj];

                        while (board[t][jj] >= '0' && board[t][jj] <= '9') {
                            inc &= board[t][jj] <= last;
                            dec &= board[t][jj] >= last;
                            ival += board[t][jj] - '0';
                            last = board[t][jj];
                            t -= 1;
                        }

                        last = new_row[jj];

                        while (board[b][jj] >= '0' && board[b][jj] <= '9') {
                            inc &= last <= board[b][jj];
                            dec &= last >= board[b][jj];
                            ival += board[b][jj] - '0';
                            last = board[b][jj];
                            b += 1;
                        }

                        if (b - t <= 2) continue;

                        ok &= (inc || dec) && ival * imul % 3 == 0;

                        if (!ok) break;

                        val += ival * imul;
                    }

                    if (!ok) continue;

                    best = max(best, val);
                }
            }
        }

        if (d == 0 || d == 2) {
            for (int i = 1; i <= row; ++i) {
                for (int j = 1; j <= col / 2; ++j) {
                    swap(board[i][j], board[i][col + 1 - j]);
                }
            }
        }

        if (d == 1) {
            for (int i = 1; i <= 20; ++i) {
                for (int j = 1; j < i; ++j) {
                    swap(board[i][j], board[j][i]);
                }
            }

            swap(row, col);
        }
    }

    cout << best << endl;

    return 0;
}
