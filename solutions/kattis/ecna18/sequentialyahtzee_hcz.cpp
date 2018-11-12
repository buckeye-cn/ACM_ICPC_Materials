// https://open.kattis.com/problems/sequentialyahtzee

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int calc_1s(int count[6]) {
    return count[0] * 1;
}

int calc_2s(int count[6]) {
    return count[1] * 2;
}

int calc_3s(int count[6]) {
    return count[2] * 3;
}

int calc_4s(int count[6]) {
    return count[3] * 4;
}

int calc_5s(int count[6]) {
    return count[4] * 5;
}

int calc_6s(int count[6]) {
    return count[5] * 6;
}

int calc_chance(int count[6]) {
    return count[0] * 1 + count[1] * 2 + count[2] * 3 + count[3] * 4 + count[4] * 5 + count[5] * 6;
}

int calc_3kind(int count[6]) {
    return calc_chance(count) * (
        count[0] >= 3 || count[1] >= 3 || count[2] >= 3 || count[3] >= 3 || count[4] >= 3 || count[5] >= 3
    );
}

int calc_4kind(int count[6]) {
    return calc_chance(count) * (
        count[0] >= 4 || count[1] >= 4 || count[2] >= 4 || count[3] >= 4 || count[4] >= 4 || count[5] >= 4
    );
}

int calc_full_house(int count[6]) {
    return 25 * (
        (count[0] == 3 || count[1] == 3 || count[2] == 3 || count[3] == 3 || count[4] == 3 || count[5] == 3)
        && (count[0] == 2 || count[1] == 2 || count[2] == 2 || count[3] == 2 || count[4] == 2 || count[5] == 2)
    );
}

int calc_small_straight(int count[6]) {
    return 30 * (
        (count[0] >= 1 && count[1] >= 1 && count[2] >= 1 && count[3] >= 1)
        || (count[1] >= 1 && count[2] >= 1 && count[3] >= 1 && count[4] >= 1)
        || (count[2] >= 1 && count[3] >= 1 && count[4] >= 1 && count[5] >= 1)
    );
}

int calc_long_straight(int count[6]) {
    return 40 * (
        (count[0] >= 1 && count[1] >= 1 && count[2] >= 1 && count[3] >= 1 && count[4] >= 1)
        || (count[1] >= 1 && count[2] >= 1 && count[3] >= 1 && count[4] >= 1 && count[5] >= 1)
    );
}

int calc_yahtzee(int count[6]) {
    return 50 * (
        count[0] >= 5 || count[1] >= 5 || count[2] >= 5 || count[3] >= 5 || count[4] >= 5 || count[5] >= 5
    );
}

int (*calc[13])(int count[6]) {
    calc_1s,
    calc_2s,
    calc_3s,
    calc_4s,
    calc_5s,
    calc_6s,
    calc_3kind,
    calc_4kind,
    calc_full_house,
    calc_small_straight,
    calc_long_straight,
    calc_chance,
    calc_yahtzee,
};

int mask[31] {
    0x01111, 0x10111, 0x11011, 0x11101, 0x11110,
    0x00111, 0x01011, 0x01101, 0x01110, 0x10011, 0x10101, 0x10110, 0x11001, 0x11010, 0x11100,
    0x00011, 0x00101, 0x00110, 0x01001, 0x01010, 0x01100, 0x10001, 0x10010, 0x10100, 0x11000,
    0x00001, 0x00010, 0x00100, 0x01000, 0x10000,
    0x00000,
};

int offset[31] {
    1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4,
    5,
};

int n;
int dice[195];

int best_seq[16];
int dp[14][195];
int step[14][195];

void dfs(int mode, int vec[5], int roll, int len, int index) {
    int count[6] {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < 5; ++i) {
        count[vec[i] - 1] += 1;
    }

    best_seq[len] = max(best_seq[len], calc[mode](count));

    if (roll < 3) {
        for (int i = 0; i < 31; ++i) {
            int newvec[5];
            int pos = 0;

            for (int j = 0; j < 5; ++j) {
                if (mask[i] & (1 << (j * 4))) {
                    newvec[pos++] = vec[j];
                }
            }

            if (index + offset[i] - 1 < n) {
                for (int j = 0; j < offset[i]; ++j) {
                    newvec[pos++] = dice[index + j];
                }

                dfs(mode, newvec, roll + 1, len + offset[i], index + offset[i]);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> dice[i];
    }

    for (int mode = 12; mode >= 0; --mode) {
        for (int i = 5 * mode; i <= min(n - 65 + 5 * mode, 15 * mode); ++i) {
            for (int j = 5; j <= 15; ++j) {
                best_seq[j] = 0;
            }

            dfs(mode, dice + i, 1, 5, i + 5);

            int best = best_seq[5] + dp[mode + 1][i + 5];
            int bestStep = 5;

            for (int j = 6; j <= 15; ++j) {
                if (i + j <= min(n - 65 + 5 * mode + 5, 15 * mode + 15) && best_seq[j] + dp[mode + 1][i + j] > best) {
                    best = best_seq[j] + dp[mode + 1][i + j];
                    bestStep = j;
                }
            }

            dp[mode][i] = best;
            step[mode][i] = bestStep;
        }
    }

    cout << dp[0][0] << endl;

    return 0;
}
