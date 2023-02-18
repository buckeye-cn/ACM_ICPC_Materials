// https://open.kattis.com/problems/commonground

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

#define OFFSET 1073741824

using namespace std;

long gcd(long y, long x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

int n;
long l, w;

int bt_n;
int bt_next[16000000][2];
int bt_level[16000000];
int bt_sum[16000000];

void fix(int p, int i) {
    if (!bt_level[p]) {
        bt_sum[p] = bt_sum[bt_next[p][0]] + bt_sum[bt_next[p][1]];
    }
}

void insert(int lb, int rb) {
    // cerr << lb << ' ' << rb << ' ' << 1 << endl;

    lb += OFFSET - 1;
    rb += OFFSET;

    int lp[31];
    int rp[31];

    lp[30] = 1;
    rp[30] = 1;

    for (int i = 30; true; --i) {
        int lbit = (lb >> i) & 1;
        int rbit = (rb >> i) & 1;

        if ((lb ^ rb) >> (i + 1)) {
            if (!lbit) {
                int &p = bt_next[lp[i]][1];

                if (!p) {
                    p = bt_n;
                    bt_n += 1;
                }

                bt_level[p] += 1;
                bt_sum[p] = 1 << i;
            }

            if (rbit) {
                int &p = bt_next[rp[i]][0];

                if (!p) {
                    p = bt_n;
                    bt_n += 1;
                }

                bt_level[p] += 1;
                bt_sum[p] = 1 << i;
            }
        }

        if (!i) break;

        if (!bt_next[lp[i]][lbit]) {
            bt_next[lp[i]][lbit] = bt_n;
            bt_n += 1;
        }

        lp[i - 1] = bt_next[lp[i]][lbit];

        if (!bt_next[rp[i]][rbit]) {
            bt_next[rp[i]][rbit] = bt_n;
            bt_n += 1;
        }

        rp[i - 1] = bt_next[rp[i]][rbit];
    }

    for (int i = 0; i <= 30; ++i) {
        fix(lp[i], i);
        fix(rp[i], i);
    }
}

void remove(int lb, int rb) {
    // cerr << lb << ' ' << rb << ' ' << -1 << endl;

    lb += OFFSET - 1;
    rb += OFFSET;

    int lp[31];
    int rp[31];

    lp[30] = 1;
    rp[30] = 1;

    for (int i = 30; true; --i) {
        int lbit = (lb >> i) & 1;
        int rbit = (rb >> i) & 1;

        if ((lb ^ rb) >> (i + 1)) {
            if (!lbit) {
                int &p = bt_next[lp[i]][1];

                if (!p) {
                    p = bt_n;
                    bt_n += 1;
                }

                bt_level[p] -= 1;
                fix(p, i - 1);
            }

            if (rbit) {
                int &p = bt_next[rp[i]][0];

                if (!p) {
                    p = bt_n;
                    bt_n += 1;
                }

                bt_level[p] -= 1;
                fix(p, i - 1);
            }
        }

        if (!i) break;

        if (!bt_next[lp[i]][lbit]) {
            bt_next[lp[i]][lbit] = bt_n;
            bt_n += 1;
        }

        lp[i - 1] = bt_next[lp[i]][lbit];

        if (!bt_next[rp[i]][rbit]) {
            bt_next[rp[i]][rbit] = bt_n;
            bt_n += 1;
        }

        rp[i - 1] = bt_next[rp[i]][rbit];
    }

    for (int i = 0; i <= 30; ++i) {
        fix(lp[i], i);
        fix(rp[i], i);
    }
}

long query(int lb, int rb) {
    lb += OFFSET - 1;
    rb += OFFSET;

    int lp = 1;
    int rp = 1;
    bool ldone = 0;
    bool rdone = 0;
    long result = 0;

    for (int i = 30; i >= 0; --i) {
        int lbit = (lb >> i) & 1;
        int rbit = (rb >> i) & 1;

        ldone = ldone || bt_level[lp];
        rdone = rdone || bt_level[rp];

        if ((lb ^ rb) >> (i + 1)) {
            result += ldone ? !lbit << i : !lbit * bt_sum[bt_next[lp][1]];
            result += rdone ? rbit << i : rbit * bt_sum[bt_next[rp][0]];
        }

        lp = bt_next[lp][lbit];
        rp = bt_next[rp][rbit];
    }

    // cerr << 'q' << lb - OFFSET + 1 << ' ' << rb - OFFSET << ' ' << result << endl;

    return result;
}

long handle(vector<pair<int, pair<int, int>>> &s) {
    int prev = 0;
    int prev_p = 0;
    long result = 0;

    bt_n = 2;
    memset(bt_next, 0, sizeof(bt_next));
    memset(bt_level, 0, sizeof(bt_level));
    memset(bt_sum, 0, sizeof(bt_sum));

    for (pair<int, pair<int, int>> p: s) {
        if (prev < p.first) {
            int lb1 = max(-prev, prev - 2 * int(w));
            int rb1 = min(prev, 2 * int(l) - prev);
            long p1 = prev_p >= 0 ? prev_p : query(lb1, rb1);

            int lb2 = max(-p.first, p.first - 2 * int(w));
            int rb2 = min(p.first, 2 * int(l) - p.first);
            long p2 = query(lb2, rb2);

            result += (p1 + p2) * (p.first - prev);
            prev = p.first;
            prev_p = p2;
        }

        if (p.second.first < p.second.second) {
            insert(p.second.first, p.second.second);
            prev_p = -1;
        } else if (p.second.first > p.second.second) {
            remove(p.second.second, p.second.first);
            prev_p = -1;
        }
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> l >> w;

    vector<pair<int, pair<int, int>>> s1;
    vector<pair<int, pair<int, int>>> s2;

    s1.push_back({l, pair<int, int>{0, 0}});
    s1.push_back({w, pair<int, int>{0, 0}});
    s1.push_back({l + w, pair<int, int>{0, 0}});

    for (int i = 0; i < n; ++i) {
        long x, y, r;
        cin >> x >> y >> r;

        long lb = min(max(x - y - r, -w), l);
        long rb = min(max(x - y + r, -w), l);

        s1.push_back({min(max(x + y - r, 0l), l + w), pair<int, int>{lb, rb}});
        s1.push_back({min(max(x + y + r, 0l), l + w), pair<int, int>{rb, lb}});
        if (x - y + r > 0 && x - y + r < l) s1.push_back({x - y + r, pair<int, int>{0, 0}});
        if (x - y + r > l - w && x - y + r < l) s1.push_back({l * 2 - (x - y + r), pair<int, int>{0, 0}});
        if (y - x + r > 0 && y - x + r < w) s1.push_back({y - x + r, pair<int, int>{0, 0}});
        if (y - x + r > w - l && y - x + r < w) s1.push_back({w * 2 - (y - x + r), pair<int, int>{0, 0}});
    }

    s2.push_back({l, pair<int, int>{0, 0}});
    s2.push_back({w, pair<int, int>{0, 0}});
    s2.push_back({l + w, pair<int, int>{0, 0}});

    for (int i = 0; i < n; ++i) {
        long x, y, r;
        cin >> x >> y >> r;

        long lb = min(max(x - y - r, -w), l);
        long rb = min(max(x - y + r, -w), l);

        s2.push_back({min(max(x + y - r, 0l), l + w), pair<int, int>{lb, rb}});
        s2.push_back({min(max(x + y + r, 0l), l + w), pair<int, int>{rb, lb}});
        if (x - y + r > 0 && x - y + r < l) s2.push_back({x - y + r, pair<int, int>{0, 0}});
        if (x - y + r > l - w && x - y + r < l) s2.push_back({l * 2 - (x - y + r), pair<int, int>{0, 0}});
        if (y - x + r > 0 && y - x + r < w) s2.push_back({y - x + r, pair<int, int>{0, 0}});
        if (y - x + r > w - l && y - x + r < w) s2.push_back({w * 2 - (y - x + r), pair<int, int>{0, 0}});
    }

    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    vector<pair<int, pair<int, int>>> s3(s1.size() + s2.size());

    merge(s1.begin(), s1.end(), s2.begin(), s2.end(), s3.begin());

    long area1 = handle(s1);
    long area2 = handle(s2);
    long area3 = area1 + area2 - handle(s3);
    long g = gcd(area3, area1);

    if (area3) {
        cout << area3 / g << '/' << area1 / g << endl;
    } else {
        cout << "0/1" << endl;
    }

    return 0;
}
