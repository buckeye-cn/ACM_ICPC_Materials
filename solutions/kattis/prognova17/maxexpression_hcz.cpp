// https://open.kattis.com/problems/maxexpression
// not AC yet

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n, n0, n1, n2;

int add, add0, add1, add2;
int addseq[52];
long dp[2][5200][5200];
long addresult;

int sub, sub0, sub1, sub2;
int subseq[52];
long subresult;

void alloc(int s, int a, int b, int c, int &d, int &e, int &f) {
    d = min(a, s);
    e = min(a + b, s) - d;
    f = min(a + b + c, s) - d - e;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;

    cin >> n >> s >> n0 >> n1 >> n2;

    char mode = '+';
    int seq = 1;

    for (int i = 1; i < s.size(); i += 2) {
        if (s[i] == '+' || s[i] == '-') {
            if (mode == '+') {
                add += seq;
                addseq[seq] += 1;
            } else {
                sub += seq;
                subseq[seq] += 1;
            }
            mode = s[i];
            seq = 0;
        }

        seq += 1;
    }

    if (mode == '+') {
        add += seq;
        addseq[seq] += 1;
    } else {
        sub += seq;
        subseq[seq] += 1;
    }

    alloc(add, n2, n1, n0, add2, add1, add0);
    alloc(sub, n0, n1, n2, sub0, sub1, sub2);

    // add

    for (int i = 63; i > 0; --i) {
        for (; addseq[i] > 0 && add2 >= i; --addseq[i]) {
            addresult += 1l << i;

            add2 -= i;
        }
    }

    bool t = false;
    int k = add0 + add1 + add2;
    for (int i = 63; i > 0; --i) {
        for (; addseq[i] > 0; --addseq[i]) {
            memset(dp[t], 0, sizeof(dp[t]));
            for (int k2 = 0; k2 <= add2 && k2 <= k; ++k2) {
                for (int k1 = 0; k1 <= add1 && k1 + k2 <= k; ++k1) {
                    int k0 = k - k1 - k2;

                    int k0x, k1x, k2x;

                    // case 1

                    alloc(i, k2, k1, k0, k2x, k1x, k0x);

                    if (k0 == k0x) {
                        dp[t][k2x][k1x] = max(dp[t][k2x][k1x], dp[!t][k2][k1] + (1l << (k2 - k2x)));
                    } else {
                        dp[t][k2x][k1x] = max(dp[t][k2x][k1x], dp[!t][k2][k1]);
                    }

                    // case 2

                    alloc(i, k0, k1, k2, k0x, k1x, k2x);

                    dp[t][k2x][k1x] = max(dp[t][k2x][k1x], dp[!t][k2][k1]);
                }
            }
            t = !t;
            k -= i;
        }
    }

    addresult += dp[!t][0][0];

    // sub

    for (int i = 63; i > 0; --i) {
        for (; subseq[i] > 0 && sub0 >= 1; --subseq[i]) {
            sub0 -= 1;

            int k0x, k1x, k2x;

            alloc(i - 1, sub2, sub1, sub0, k2x, k1x, k0x);

            sub2 -= k2x;
            sub1 -= k1x;
            sub0 -= k0x;
        }
    }

    for (int i = 63; i > 0; --i) {
        if (sub1 >= subseq[i]) {
            subseq[i - 1] += subseq[i];
            subseq[i] = 0;

            sub1 -= subseq[i];
        } else {
            subseq[i - 1] += sub1;
            subseq[i] -= sub1;

            sub1 = 0;
        }
    }

    for (int i = 63; i >= 0; --i) { // notice: includes 0
        for (; subseq[i] > 0; --subseq[i]) {
            subresult -= 1l << i;

            sub2 -= i;
        }
    }

    cout << addresult + subresult << endl;
    // cout << addresult << endl;
    // cout << subresult << endl;

    return 0;
}
