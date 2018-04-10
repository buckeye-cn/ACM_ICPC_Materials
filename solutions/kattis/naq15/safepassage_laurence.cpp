#include <algorithm>
#include <iostream>

using namespace std;

uint32_t TT[16] = {};

struct St {
    uint16_t l, r;

    bool last_two() const {
        return __builtin_popcount(l) == 2;
    }

    uint32_t tlt() const {
        uint8_t i1, i2;
        uint16_t _l = l;
        i1 = __builtin_ctz(_l); _l ^= 1 << i1;
        i2 = __builtin_ctz(_l);

        return TT[i2];
    }

    uint32_t tltr0(St& nst) const {
        uint8_t i1, i2, i3;
        uint16_t _l = l, _r = r;
        i1 = __builtin_ctz(_l); _l ^= 1 << i1; _r ^= 1 << i1;
        i2 = __builtin_ctz(_l); _l ^= 1 << i2; _r ^= 1 << i2;
        i3 = __builtin_ctz(_r); _l ^= 1 << i3; _r ^= 1 << i3;

        nst.l = _l; nst.r = _r;
        return TT[i2] + TT[i3];
    }

    uint32_t tltr1(St& nst) const {
        uint8_t i1, i2, i3;
        uint16_t _b1, _l = l, _r = r;
        _b1 = _l & -_l;
        _l ^= _b1;
        i1 = __builtin_ctz(_l); _l ^= 1 << i1; _r ^= 1 << i1;
        i2 = __builtin_ctz(_l); _l ^= 1 << i2; _r ^= 1 << i2;
        i3 = __builtin_ctz(_r); _l ^= 1 << i3; _r ^= 1 << i3;
        _l ^= _b1;

        nst.l = _l; nst.r = _r;
        return TT[i2] + TT[i3];
    }

    uint32_t dd() const {
        if (last_two()) {
            return tlt();
        } else {
            St nst0, nst1;
            uint32_t ts0 = tltr0(nst0), ts1 = tltr1(nst1);
            return min(nst0.dd() + ts0, nst1.dd() + ts1);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint16_t N;
    cin >> N;

    for (uint8_t i = 0; i < N; i++) {
        int16_t t;
        cin >> t;
        TT[i] = t;
    }

    sort(begin(TT), begin(TT)+N);

    cout << St { (uint16_t)((1 << N) - 1), 0 }.dd() << endl;
}
