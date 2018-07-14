#include <algorithm>
#include <iostream>

using namespace std;

typedef int64_t i64;

constexpr uint8_t
    Pttp_MSR_B = 1, Pttp_MSR_E = 2,
    Pttp_SUN_B = 4, Pttp_SUN_E = 8,
    Pttp_W = 010, Pttp_MASK = (1 << Pttp_W) - 1;

struct Intr {
    i64 b, e;
    bool operator<(Intr o) const noexcept { return b < o.b || (b == o.b && e < o.e); }
};

i64 data[60000];

i64* const pts = data; size_t pts_c = 0;
void pt_insert(i64 t, i64 tp) { pts[pts_c++] = ((t << Pttp_W) | tp); };

Intr GG[size_t(1e7l+1)]; size_t gg_c = 0;
void gg_insert(i64 b, i64 e, i64 offset) {
    GG[gg_c].b = b - offset; if (GG[gg_c].b < 0) GG[gg_c].b = 0;
    GG[gg_c].e = e - offset;
    gg_c++;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint16_t N, K;
    i64 t1, t2;
    cin >> N >> K >> t1 >> t2;
    i64 dt = t2 - t1;

    for (uint16_t i = 0; i < N; i++) {
        i64 m;
        cin >> m;
        pt_insert(m, Pttp_MSR_B);
        pt_insert(m+dt, Pttp_MSR_E);
    }
    for (uint16_t i = 0; i < K; i++) {
        i64 b, e;
        cin >> b >> e;
        b -= t1; b = b < 0 ? 0 : b;
        e -= t1; e = e < 0 ? 0 : e;
        if (e > 0) {
            pt_insert(b, Pttp_SUN_B);
            pt_insert(e, Pttp_SUN_E);
        }
    }
    sort(pts, pts+pts_c);

    uint8_t state = 0;
    i64 *msr_b = data + (N+K+2)*2, msr_b_f = 0, msr_b_c = 0, sun_b = 0;
    for (size_t i = 0; i < pts_c; i++) {
        i64 tp = pts[i] & Pttp_MASK;
        i64 ti = pts[i] >> Pttp_W;
        switch (tp) {
            case Pttp_MSR_B:
                msr_b[msr_b_c++] = ti;
                state |= tp;
                break;
            case Pttp_SUN_B:
                sun_b = ti;
                state |= tp;
                break;
            case Pttp_MSR_E:
                if (state == (Pttp_MSR_B | Pttp_SUN_B))
                    for (i64 j = msr_b_f; j < msr_b_c; j++)
                        gg_insert(sun_b, ti, msr_b[j]);
                if (++msr_b_f == msr_b_c)
                    state &= ~Pttp_MSR_B;
                break;
            case Pttp_SUN_E:
                if (state == (Pttp_MSR_B | Pttp_SUN_B))
                    for (i64 j = msr_b_f; j < msr_b_c; j++)
                        gg_insert(sun_b, ti, msr_b[j]);
                sun_b = 0;
                state &= ~Pttp_SUN_B;
                break;
            default:
                return 1;
        }
    }
    sort(GG, GG+gg_c);

    i64 tot = 0;
    if (gg_c) {
        Intr cur { GG[0] };
        for (size_t i = 1; i < gg_c; i++) {
            if (cur.e < GG[i].b) {
                tot += cur.e - cur.b;
                cur.b = GG[i].b;
            }
            cur.e = max(cur.e, GG[i].e);
        }
        tot += cur.e - cur.b;
    }
    cout << float(dt - tot) / float(dt) << '\n';
}
