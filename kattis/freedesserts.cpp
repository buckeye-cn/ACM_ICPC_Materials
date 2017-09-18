// https://open.kattis.com/problems/freedesserts
// not AC yet

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

// iter, map_a, map_b, carry
int cases[2][1024][1024][2][2][2];
string s;
int set_d;

int main() {
    ios_base::sync_with_stdio(false);
    cout.precision(10);

    cin >> s;

    for (int i = 0; i < s.size(); ++i) {
        set_d |= (1 << (s[i] - '0'));
    }

    int d0 = s[s.size() - 1] - '0';
    for (int a = 0; a <= 9; ++a) {
        for (int b = 0; b <= 9; ++b) {
            if (a + b == d0) {
                cases[0][1 << a][1 << b][0][false][false] = 1;
                cases[0][1 << a][1 << b][0][false][true] = 1;
                cases[0][1 << a][1 << b][0][true][false] = 1;
                cases[0][1 << a][1 << b][0][true][true] = 1;
            }
            if (a + b == d0 + 10) {
                cases[0][1 << a][1 << b][1][false][false] = 1;
                cases[0][1 << a][1 << b][1][false][true] = 1;
                cases[0][1 << a][1 << b][1][true][false] = 1;
                cases[0][1 << a][1 << b][1][true][true] = 1;
            }
        }
    }

    for (int i = 1; i < s.size(); ++i) {
        int d = s[s.size() - 1 - i] - '0';

        memset(&cases[i & 1], 0, sizeof(cases[i & 1]));

        for (int set_a = 0; set_a < 1024; ++set_a) {
            if (set_a & set_d) continue;

            for (int set_b = 0; set_b < 1024; ++set_b) {
                if (set_b & set_d) continue;
                if (set_b & set_a) continue;

                for (int a = 0; a <= 9; ++a) {
                    for (int b = 0; b <= 9; ++b) {
                        if (a + b == d) {
                            cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][false][false] +=
                                cases[1 ^ (i & 1)][set_a][set_b][0][false][false];
                            if (b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][false][true] +=
                                cases[1 ^ (i & 1)][set_a][set_b][0][false][false];
                            if (a) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][true][false] +=
                                cases[1 ^ (i & 1)][set_a][set_b][0][false][false];
                            if (a && b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][true][true] +=
                                cases[1 ^ (i & 1)][set_a][set_b][0][false][false];
                        }
                        if (a + b + 1 == d) {
                            cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][false][false] +=
                                cases[1 ^ (i & 1)][set_a][set_b][1][false][false];
                            if (b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][false][true] +=
                                cases[1 ^ (i & 1)][set_a][set_b][1][false][false];
                            if (a) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][true][false] +=
                                cases[1 ^ (i & 1)][set_a][set_b][1][false][false];
                            if (a && b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][true][true] +=
                                cases[1 ^ (i & 1)][set_a][set_b][1][false][false];
                        }
                        if (a + b == d + 10) {
                            cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][false][false] +=
                                cases[1 ^ (i & 1)][set_a][set_b][0][false][false];
                            if (b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][false][true] +=
                                cases[1 ^ (i & 1)][set_a][set_b][0][false][false];
                            if (a) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][true][false] +=
                                cases[1 ^ (i & 1)][set_a][set_b][0][false][false];
                            if (a && b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][true][true] +=
                                cases[1 ^ (i & 1)][set_a][set_b][0][false][false];
                        }
                        if (a + b + 1 == d + 10) {
                            cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][false][false] +=
                                cases[1 ^ (i & 1)][set_a][set_b][1][false][false];
                            if (b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][false][true] +=
                                cases[1 ^ (i & 1)][set_a][set_b][1][false][false];
                            if (a) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][true][false] +=
                                cases[1 ^ (i & 1)][set_a][set_b][1][false][false];
                            if (a && b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][true][true] +=
                                cases[1 ^ (i & 1)][set_a][set_b][1][false][false];
                        }
                    }
                }
                for (int a = 0; a <= 9; ++a) {
                    if (a == d) {
                        cases[i & 1][set_a | (1 << a)][set_b][0][false][true] +=
                            cases[1 ^ (i & 1)][set_a][set_b][0][false][true];
                        if (a) cases[i & 1][set_a | (1 << a)][set_b][0][true][true] +=
                            cases[1 ^ (i & 1)][set_a][set_b][0][false][true];
                    }
                    if (a + 1 == d) {
                        cases[i & 1][set_a | (1 << a)][set_b][0][false][true] +=
                            cases[1 ^ (i & 1)][set_a][set_b][1][false][true];
                        if (a) cases[i & 1][set_a | (1 << a)][set_b][0][true][true] +=
                            cases[1 ^ (i & 1)][set_a][set_b][1][false][true];
                    }
                    if (a + 1 == d + 10) {
                        cases[i & 1][set_a | (1 << a)][set_b][1][false][true] +=
                            cases[1 ^ (i & 1)][set_a][set_b][1][false][true];
                        if (a) cases[i & 1][set_a | (1 << a)][set_b][1][true][true] +=
                            cases[1 ^ (i & 1)][set_a][set_b][1][false][true];
                    }
                }
                for (int b = 0; b <= 9; ++b) {
                    if (b == d) {
                        cases[i & 1][set_a][set_b | (1 << b)][0][true][false] +=
                            cases[1 ^ (i & 1)][set_a][set_b][0][true][false];
                        if (b) cases[i & 1][set_a][set_b | (1 << b)][0][true][true] +=
                            cases[1 ^ (i & 1)][set_a][set_b][0][true][false];
                    }
                    if (b + 1 == d) {
                        cases[i & 1][set_a][set_b | (1 << b)][0][true][false] +=
                            cases[1 ^ (i & 1)][set_a][set_b][1][true][false];
                        if (b) cases[i & 1][set_a][set_b | (1 << b)][0][true][true] +=
                            cases[1 ^ (i & 1)][set_a][set_b][1][true][false];
                    }
                    if (b + 1 == d + 10) {
                        cases[i & 1][set_a][set_b | (1 << b)][1][true][false] +=
                            cases[1 ^ (i & 1)][set_a][set_b][1][true][false];
                        if (b) cases[i & 1][set_a][set_b | (1 << b)][1][true][true] +=
                            cases[1 ^ (i & 1)][set_a][set_b][1][true][false];
                    }
                }
                if (0 == d) {
                    cases[i & 1][set_a][set_b][0][true][true] +=
                        cases[1 ^ (i & 1)][set_a][set_b][0][true][true];
                }
                if (1 == d) {
                    cases[i & 1][set_a][set_b][0][true][true] +=
                        cases[1 ^ (i & 1)][set_a][set_b][1][true][true];
                }
            }
        }

        // cout << d << endl;
        // for (int set_a = 0; set_a < 1024; ++set_a) {
        //     if (set_a & set_d) continue;

        //     for (int set_b = 0; set_b < 1024; ++set_b) {
        //         if (set_b & set_d) continue;
        //         if (set_b & set_a) continue;

        //         if (cases[1 ^ (i & 1)][set_a][set_b][1][true][true]) {
        //             printf("last %x %x %x %d\n", set_d, set_a, set_b, cases[1 ^ (i & 1)][set_a][set_b][1][true][true]);
        //         }
        //         if (cases[i & 1][set_a][set_b][0][true][true]) {
        //             printf("this %x %x %x %d\n", set_d, set_a, set_b, cases[i & 1][set_a][set_b][0][true][true]);
        //         }
        //     }
        // }
    }

    int global_tot = 0;

    for (int set_a = 0; set_a < 1024; ++set_a) {
        if (set_a & set_d) continue;

        for (int set_b = 0; set_b < 1024; ++set_b) {
            if (set_b & set_d) continue;
            if (set_b & set_a) continue;

            global_tot += cases[1 ^ (s.size() & 1)][set_a][set_b][0][true][true];
        }
    }

    cout << global_tot / 2 << endl;

    return 0;
}
