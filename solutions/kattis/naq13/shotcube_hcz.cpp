// https://open.kattis.com/problems/shotcube

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

#define MASK_H (1l | (1l << 1) | (1l << 2) | (1l << 3) | (1l << 4) | (1l << 5) | (1l << 6))
#define MASK_V (1l | (1l << 7) | (1l << 14) | (1l << 21) | (1l << 28) | (1l << 35) | (1l << 42))

using namespace std;

int q_head;
int q_tail;
pair<long, int> q[2000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    unordered_multimap<long, long> shot_h;
    unordered_multimap<long, long> shot_v;

    for (long i = 1; i <= 5; ++i) {
        for (long j = 1; i + j <= 6; ++j) {
            for (long k = 0; k < 1l << (6 - i - j); ++k) {
                long i_mask = (1l << i) - 1;
                shot_h.insert({
                    (i_mask << j) | (1l << (i + j)) | (k << (i + j + 1)),
                    (i_mask << 0) | (1l << (i + j)) | (k << (i + j + 1))
                });
                shot_h.insert({
                    (i_mask << (7 - i - j)) | (1l << (6 - i - j)) | (k << 0),
                    (i_mask << (7 - i    )) | (1l << (6 - i - j)) | (k << 0)
                });
            }
        }
    }

    for (const pair<long, long> &i: shot_h) {
        pair<long, long> vert {0, 0};

        for (long j = 0; j < 7; ++j) {
            vert.first |= ((i.first >> j) & 1) << (7 * j);
            vert.second |= ((i.second >> j) & 1) << (7 * j);
        }

        shot_v.insert(vert);
    }

    unordered_map<long, int> cache;

    for (long i = 0; i <= 28; i += 7) {
        for (long j = i; j <= i + 4; j += 1) {
            pair<long, int> p {(7l | (7l << 7) | (7l << 14)) << j, 0};

            q[q_tail++] = p;
            cache.insert(p);
        }
    }

    while (q_head != q_tail) {
        pair<long, int> p = q[q_head++];

        for (long i = 0; i < 49; i += 7) {
            long line = (p.first >> i) & MASK_H;

            auto range = shot_h.equal_range(line);

            for (auto iter = range.first; iter != range.second; ++iter) {
                pair<long, int> new_p {
                    (p.first & ~(MASK_H << i)) | (iter->second << i),
                    p.second + 1
                };

                if (cache.find(new_p.first) == cache.end()) {
                    q[q_tail++] = new_p;
                    cache.insert(new_p);
                }
            }
        }

        for (long i = 0; i < 7; i += 1) {
            long line = (p.first >> i) & MASK_V;

            auto range = shot_v.equal_range(line);

            for (auto iter = range.first; iter != range.second; ++iter) {
                pair<long, int> new_p {
                    (p.first & ~(MASK_V << i)) | (iter->second << i),
                    p.second + 1
                };

                if (cache.find(new_p.first) == cache.end()) {
                    q[q_tail++] = new_p;
                    cache.insert(new_p);
                }
            }
        }
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        long v = 0;

        for (long j = 0; j < 49; ++j) {
            char c;
            cin >> c;

            if (c == 'X') {
                v |= 1l << j;
            }
        }

        if (cache.find(v) == cache.end()) {
            cout << -1 << endl;
        } else {
            cout << cache[v] << endl;
        }
    }

    return 0;
}
