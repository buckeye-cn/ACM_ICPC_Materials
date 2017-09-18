#include <iostream>

using namespace std;

const int PRI[7][7] = {
    { 0, 0, 0, 0, 0, 0, 0 },  // 0
    { 0, 24, 30, 6, 8, 11, 15 },
    { 0, 30, 25, 7, 9, 12, 16 },
    { 0, 6, 7, 26, 10, 13, 17 },
    { 0, 8, 9, 10, 27, 14, 18 },
    { 0, 11, 12, 13, 14, 28, 19 },
    { 0, 15, 16, 17, 18, 19, 29 },
};

int gcd(int a, int b) {
    if (b != 0) {
        return gcd(b, a % b);
    } else {
        return a;
    }
}

void print_frac(int a, int b) {
    if (a == 0) {
        cout << "0" << endl;
    } else if (a == b) {
        cout << "1" << endl;
    } else {
        int _gcd = gcd(b, a);
        cout << a/_gcd << "/" << b/_gcd << endl;
    }
}

int main() {
    while (true) {
        char line[4];
        cin >> line[0] >> line[1] >> line[2] >> line[3];
        if (
                line[0] == '0' &&
                line[1] == '0' &&
                line[2] == '0' &&
                line[3] == '0'
        ) {
            break;
        }

        int num[4];
        for (int i = 0; i < 4; i++) {
            if (line[i] == '*') {
                num[i] = 0;
            } else {
                num[i] = (int)line[i] - (int)'0';
            }
        }

        if (
                num[0] != 0 &&
                num[1] != 0 &&
                num[2] != 0 &&
                num[3] != 0
        ) {
            int p1 = PRI[num[0]][num[1]];
            int p2 = PRI[num[2]][num[3]];
            if (p1 > p2) {
                cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
        } else if (
                num[0] == 0 &&
                num[1] == 0 &&
                num[2] == 0 &&
                num[3] == 0
        ) {
            cout << "205/432" << endl;
        } else if (
                num[0] == 0 &&
                num[1] == 0 &&
                num[2] != 0 &&
                num[3] != 0
        ) {
            int p2 = PRI[num[2]][num[3]];
            int win = 0;
            for (int i = 1; i <= 6; i++) {
                for (int j = 1; j <= 6; j++) {
                    if (PRI[i][j] > p2) {
                        win += 1;
                    }
                }
            }
            print_frac(win, 36);
        } else if (
                num[0] != 0 &&
                num[1] != 0 &&
                num[2] == 0 &&
                num[3] == 0
        ) {
            int p1 = PRI[num[0]][num[1]];
            int win = 0;
            for (int i = 1; i <= 6; i++) {
                for (int j = 1; j <= 6; j++) {
                    if (p1 > PRI[i][j]) {
                        win += 1;
                    }
                }
            }
            print_frac(win, 36);
        } else if (num[2] != 0 && num[3] != 0) {
            int d1 = (num[0] != 0) ? num[0] : num[1];
            int p2 = PRI[num[2]][num[3]];
            int win = 0;
            for (int i = 1; i <= 6; i++) {
                if (PRI[d1][i] > p2) {
                    win += 1;
                }
            }
            print_frac(win, 6);
        } else if (num[0] != 0 && num[1] != 0) {
            int d1 = (num[2] != 0) ? num[2] : num[3];
            int p1 = PRI[num[0]][num[1]];
            int win = 0;
            for (int i = 1; i <= 6; i++) {
                if (p1 > PRI[d1][i]) {
                    win += 1;
                }
            }
            print_frac(win, 6);
        } else {
            int d1 = (num[0] != 0) ? num[0] : num[1];
            int d2 = (num[2] != 0) ? num[2] : num[3];
            int win = 0;

            if (d1 != 0 && d2 != 0) {
                for (int i = 1; i <= 6; i++) {
                    for (int j = 1; j <= 6; j++) {
                        if (PRI[d1][i] > PRI[d2][j]) {
                            win += 1;
                        }
                    }
                }
                print_frac(win, 36);
            } else if (d1 == 0) {
                for (int i = 1; i <= 6; i++) {
                    for (int j = 1; j <= 6; j++) {
                        for (int k = 1; k <= 6; k++) {
                            if (PRI[i][j] > PRI[d2][k]) {
                                win += 1;
                            }
                        }
                    }
                }
                print_frac(win, 216);
            } else {
                for (int i = 1; i <= 6; i++) {
                    for (int j = 1; j <= 6; j++) {
                        for (int k = 1; k <= 6; k++) {
                            if (PRI[d1][i] > PRI[j][k]) {
                                win += 1;
                            }
                        }
                    }
                }
                print_frac(win, 216);
            }
        }
    }
}
