// https://open.kattis.com/problems/estheticfences

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

uint32_t h[1048576];
char r[1048576];
char b[1048576];
int len[1048576];
int rr[200000];
int rb[200000];
int bb[200000];
bool seen1[1048576];
bool seen2[1048576];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    int nrr = 0;
    int nrb = 0;
    int nbb = 0;

    for (int i = 0; i < n; ++i) {
        int l;
        char c;
        cin >> l >> c;

        uint32_t hash = (l * 0x23456789u) ^ ((l + c) * 0x67892345u);

        for (int j = 0; j < (1 << i); ++j) {
            h[j | (1 << i)] = h[j] + hash;
            r[j | (1 << i)] = r[j] + (c == 'r');
            b[j | (1 << i)] = b[j] + (c == 'b');
            len[j | (1 << i)] = len[j] + l;

            if (r[j | (1 << i)] == b[j | (1 << i)] + 1) {
                rr[nrr] = j | (1 << i);
                nrr += 1;
            } else if (r[j | (1 << i)] == b[j | (1 << i)]) {
                rb[nrb] = j | (1 << i);
                nrb += 1;
            } else if (r[j | (1 << i)] + 1 == b[j | (1 << i)]) {
                bb[nbb] = j | (1 << i);
                nbb += 1;
            }
        }
    }

    int best = 0;

    for (int i = 0; i < nrr; ++i) {
        if (seen1[h[rr[i]] >> 12]) continue;
        seen1[h[rr[i]] >> 12] = true;
        seen1[h[rr[i]] & 1048575] = true;

        int len_i = len[rr[i]];

        for (int j = 0; j < nrb; ++j) {
            if (rr[i] & rb[j]) continue;

            if (seen2[h[rb[j]] >> 12]) continue;
            seen2[h[rb[j]] >> 12] = true;
            seen2[h[rb[j]] & 1048575] = true;

            int len_j = len[rb[j]];

            for (int k = 0; k < nbb; ++k) {
                if (rr[i] & bb[k]) continue;
                if (rb[j] & bb[k]) continue;

                int len_k = len[bb[k]];

                if (len_i < len_j + len_k && len_j < len_i + len_k && len_k < len_i + len_j) {
                    best = max(best, len_i * len_j * len_k);
                }
            }
        }

        for (int j = 0; j < nrb; ++j) {
            seen2[h[rb[j]] >> 12] = false;
            seen2[h[rb[j]] & 1048575] = false;
        }
    }

    for (int i = 0; i < nrr; ++i) {
        seen1[h[rr[i]] >> 12] = false;
        seen1[h[rr[i]] & 1048575] = false;
    }

    for (int i = 0; i < nrb; ++i) {
        if (seen1[h[rb[i]] >> 12]) continue;
        seen1[h[rb[i]] >> 12] = true;
        seen1[h[rb[i]] & 1048575] = true;

        int len_i = len[rb[i]];

        for (int j = i + 1; j < nrb; ++j) {
            if (rb[i] & rb[j]) continue;

            if (seen2[h[rb[j]] >> 12]) continue;
            seen2[h[rb[j]] >> 12] = true;
            seen2[h[rb[j]] & 1048575] = true;

            int len_j = len[rb[j]];

            for (int k = j + 1; k < nrb; ++k) {
                if (rb[i] & rb[k]) continue;
                if (rb[j] & rb[k]) continue;

                int len_k = len[rb[k]];

                if (len_i < len_j + len_k && len_j < len_i + len_k && len_k < len_i + len_j) {
                    best = max(best, len_i * len_j * len_k);
                }
            }
        }

        for (int j = i + 1; j < nrb; ++j) {
            seen2[h[rb[j]] >> 12] = false;
            seen2[h[rb[j]] & 1048575] = false;
        }
    }

    cout << best << endl;

    return 0;
}
