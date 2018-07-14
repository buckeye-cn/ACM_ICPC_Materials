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

i64 data[40001+10001+20000001];

i64* const pts = data; i64* pts_c = pts;
void pt_insert(i64 t, i64 tp) { *pts_c++ = ((t << Pttp_W) | tp); };

Intr* const GG = (Intr*)(data+40001+10001) ; Intr* gg_c = GG;
void gg_insert(i64 b, i64 e, i64 offset) {
    gg_c->b = b - offset; if (gg_c->b < 0) gg_c->b = 0;
    gg_c->e = e - offset;
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
        pt_insert(t1+m, Pttp_MSR_B);
        pt_insert(t1+m+dt, Pttp_MSR_E);
    }
    for (uint16_t i = 0; i < K; i++) {
        i64 b, e;
        cin >> b >> e;
        pt_insert(b, Pttp_SUN_B);
        pt_insert(e, Pttp_SUN_E);
    }
    sort(pts, pts_c);

    uint8_t state = 0;
    i64 *msr_b_f = data+40001, *msr_b_c = msr_b_f, sun_b = 0;
    for (i64* p = pts; p < pts_c; p++) {
        i64 tp = *p & Pttp_MASK;
        i64 ti = *p >> Pttp_W;
        switch (tp) {
            case Pttp_MSR_B:
                *msr_b_c++ = ti;
                state |= tp;
                break;
            case Pttp_SUN_B:
                sun_b = ti;
                state |= tp;
                break;
            case Pttp_MSR_E:
                if (state == (Pttp_MSR_B | Pttp_SUN_B))
                    for (i64 const* p = msr_b_f; p < msr_b_c; p++)
                        gg_insert(sun_b, ti, *p);
                if (++msr_b_f == msr_b_c)
                    state &= ~Pttp_MSR_B;
                break;
            case Pttp_SUN_E:
                if (state == (Pttp_MSR_B | Pttp_SUN_B))
                    for (i64 const* p = msr_b_f; p < msr_b_c; p++)
                        gg_insert(sun_b, ti, *p);
                sun_b = 0;
                state &= ~Pttp_SUN_B;
                break;
            default:
                return 1;
        }
    }
    sort(GG, gg_c);

    i64 tot = 0;
    if (gg_c) {
        Intr cur { GG[0] };
        for (Intr const* p = GG+1; p < gg_c; p++) {
            if (cur.e < p->b) {
                tot += cur.e - cur.b;
                cur.b = p->b;
            }
            cur.e = max(cur.e, p->e);
        }
        tot += cur.e - cur.b;
    }
    cout << float(dt - tot) / float(dt) << '\n';
}
