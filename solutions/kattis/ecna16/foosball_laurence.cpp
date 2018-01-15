#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

unordered_map<uint16_t, string> i2n = {};

uint16_t WO = 1, WD = 4, WR = 0, WC = 0,
         BO = 2, BD = 8, BR = 0, BC = 0;

uint16_t _h = 0;
vector<uint16_t> hs;

queue<uint16_t> q;

#define True (1 << 15)

#define HAHA(W, L) {                                \
    W ## C++;                                       \
    L ## C = 0;                                     \
    if (W ## C >= _h) {                             \
        if (W ## C > _h) {                          \
            _h = W ## C;                            \
            hs.clear();                             \
        }                                           \
        hs.emplace_back(W ## O | W ## D | W ## R);  \
    }                                               \
    swap(W ## O, W ## D);                           \
    q.emplace(L ## D);                              \
    L ## D = L ## O;                                \
    L ## O = q.front(); q.pop();                    \
    L ## R = ( L ## D > L ## O ) ? True : 0;        \
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    unsigned short N;
    cin >> N;

    for (uint16_t i = 0; i < N; i++) {
        string n;
        cin >> n;
        i2n.emplace(1 << i, n);
    }

    for (uint16_t i = 4; i < N; i++)
        q.emplace(1 << i);

    string st;
    cin >> st;

    hs.reserve(90);

    for (const char t : st) {
        if (t == 'W') HAHA(W, B)
        else          HAHA(B, W)
    }

    for (const uint16_t t : hs) {
        uint16_t _t = t, p[2] = {};
        for (uint16_t i = 0, n = 0; t > 0; _t >>= 1, i += 1) {
            if (_t & 1) {
                p[n++] = 1 << i;
                if (n == 2) break;
            }
        }
        if (t & True) swap(p[0], p[1]);

        cout << i2n[p[0]] << ' ' << i2n[p[1]] << '\n';
    }
}
