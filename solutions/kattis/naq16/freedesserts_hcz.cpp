// https://open.kattis.com/problems/freedesserts

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

// iter, map_a, map_b, carry, fin_a, fin_b
long cases[2][1024][1024][2][2][2];
string s;
int set_d;
int need = 5000;

void iter(int index, long curr_s, long a, int set_a, long b, int set_b, long bc, int set_bc) {
    // cout << index << ' ' << a << ' ' << set_a << ' ' << b << ' ' << set_b << ' ' << bc << ' ' << set_bc << endl;
    if (index == s.size()) {
        if (set_b & set_d) return;
        if (set_b & set_a) return;

        if (a >= b) exit(0);
        cout << a << ' ' << b << endl;
        need -= 1;
        if (!need) exit(0);
    } else {
        int d = s[index] - '0';
        long new_s = curr_s * 10 + d;

        for (int i = 0; i <= 9; ++i) {
            long new_a = a * 10 + i;

            int new_set_a = set_a | (new_a ? 1 << i : 0);
            // cout << i << " a:" << new_a << '-' << new_set_a << endl;
            if (new_set_a & set_d) continue;

            long new_b = new_s - new_a;
            long new_bc = new_s - new_a - 1;

            int new_set_b, new_set_bc;
            if (d >= i) {
                new_set_b = set_b | (new_b ? 1 << (d - i) : 0);
            } else {
                new_set_b = set_bc | (new_b ? 1 << (10 + d - i) : 0);
            }
            if (d >= i + 1) {
                new_set_bc = set_b | (new_bc ? 1 << (d - i - 1) : 0);
            } else {
                new_set_bc = set_bc | (new_bc ? 1 << (10 + d - i - 1) : 0);
            }
            // cout << i << " b:" << new_b << '-' << new_set_b << " bc:" << new_bc << '-' << new_set_bc << endl;
            if ((new_set_b & set_d) && (new_set_bc & set_d)) continue;
            if ((new_set_b & new_set_a) && (new_set_bc & new_set_a)) continue;

            iter(index + 1, new_s, new_a, new_set_a, new_b, new_set_b, new_bc, new_set_bc);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> s;

    for (int i = 0; i < s.size(); ++i) {
        set_d |= (1 << (s[i] - '0'));
    }

    // digit 0

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

    // digit 1-highest

    for (int i = 1; i < s.size(); ++i) {
        int d = s[s.size() - 1 - i] - '0';

        for (int set_a = 0; set_a < 1024; ++set_a) {
            if (set_a & set_d) continue;

            for (int set_b = 0; set_b < 1024; ++set_b) {
                if (set_b & set_d) continue;
                if (set_b & set_a) continue;

                memset(&cases[i & 1][set_a][set_b], 0, sizeof(cases[i & 1][set_a][set_b]));
            }
        }

        for (int set_a = 0; set_a < 1024; ++set_a) {
            if (set_a & set_d) continue;

            for (int set_b = 0; set_b < 1024; ++set_b) {
                if (set_b & set_d) continue;
                if (set_b & set_a) continue;

                if (long count = cases[1 ^ (i & 1)][set_a][set_b][0][false][false])
                for (int a = 0; a <= 9; ++a) {
                    for (int b = 0; b <= 9; ++b) {
                        if (a + b == d) {
                            cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][false][false] += count;
                            if (b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][false][true] += count;
                            if (a) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][true][false] += count;
                            if (a && b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][true][true] += count;
                        } else if (a + b == d + 10) {
                            cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][false][false] += count;
                            if (b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][false][true] += count;
                            if (a) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][true][false] += count;
                            if (a && b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][true][true] += count;
                        }
                    }
                }
                if (long count = cases[1 ^ (i & 1)][set_a][set_b][1][false][false])
                for (int a = 0; a <= 9; ++a) {
                    for (int b = 0; b <= 9; ++b) {
                        if (a + b + 1 == d) {
                            cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][false][false] += count;
                            if (b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][false][true] += count;
                            if (a) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][true][false] += count;
                            if (a && b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][0][true][true] += count;
                        } else if (a + b + 1 == d + 10) {
                            cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][false][false] += count;
                            if (b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][false][true] += count;
                            if (a) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][true][false] += count;
                            if (a && b) cases[i & 1][set_a | (1 << a)][set_b | (1 << b)][1][true][true] += count;
                        }
                    }
                }
                if (long count = cases[1 ^ (i & 1)][set_a][set_b][0][false][true])
                for (int a = 0; a <= 9; ++a) {
                    if (a == d) {
                        cases[i & 1][set_a | (1 << a)][set_b][0][false][true] += count;
                        if (a) cases[i & 1][set_a | (1 << a)][set_b][0][true][true] += count;
                    }
                }
                if (long count = cases[1 ^ (i & 1)][set_a][set_b][1][false][true])
                for (int a = 0; a <= 9; ++a) {
                    if (a + 1 == d) {
                        cases[i & 1][set_a | (1 << a)][set_b][0][false][true] += count;
                        if (a) cases[i & 1][set_a | (1 << a)][set_b][0][true][true] += count;
                    } else if (a + 1 == d + 10) {
                        cases[i & 1][set_a | (1 << a)][set_b][1][false][true] += count;
                        if (a) cases[i & 1][set_a | (1 << a)][set_b][1][true][true] += count;
                    }
                }
                if (long count = cases[1 ^ (i & 1)][set_a][set_b][0][true][false])
                for (int b = 0; b <= 9; ++b) {
                    if (b == d) {
                        cases[i & 1][set_a][set_b | (1 << b)][0][true][false] += count;
                        if (b) cases[i & 1][set_a][set_b | (1 << b)][0][true][true] += count;
                    }
                }
                if (long count = cases[1 ^ (i & 1)][set_a][set_b][1][true][false])
                for (int b = 0; b <= 9; ++b) {
                    if (b + 1 == d) {
                        cases[i & 1][set_a][set_b | (1 << b)][0][true][false] += count;
                        if (b) cases[i & 1][set_a][set_b | (1 << b)][0][true][true] += count;
                    } else if (b + 1 == d + 10) {
                        cases[i & 1][set_a][set_b | (1 << b)][1][true][false] += count;
                        if (b) cases[i & 1][set_a][set_b | (1 << b)][1][true][true] += count;
                    }
                }
                if (long count = cases[1 ^ (i & 1)][set_a][set_b][0][true][true])
                if (0 == d) {
                    cases[i & 1][set_a][set_b][0][true][true] += count;
                }
                if (long count = cases[1 ^ (i & 1)][set_a][set_b][1][true][true])
                if (1 == d) {
                    cases[i & 1][set_a][set_b][0][true][true] += count;
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

    // sum

    long global_tot = 0;

    for (int set_a = 0; set_a < 1024; ++set_a) {
        if (set_a & set_d) continue;

        for (int set_b = 0; set_b < 1024; ++set_b) {
            if (set_b & set_d) continue;
            if (set_b & set_a) continue;

            global_tot += cases[1 ^ (s.size() & 1)][set_a][set_b][0][true][true];
        }
    }

    cout << global_tot / 2 << endl;

    // find first 5000

    iter(0, 0, 0, 0, 0, 0, 0, 0);

    return 0;
}
