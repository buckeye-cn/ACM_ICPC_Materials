#include <iostream>

using namespace std;

static inline uint32_t np2(uint32_t x);

typedef int32_t i32;

struct Pos { i32 x, y; } HOUSE[100001];

typedef Pos const* PP;

struct Node { PP x[2][2], y[2][2]; } NODES[240000];

#define Nmin 0
#define Nmax 1

static inline void init(Node* n, PP p) {
    n->x[Nmin][0] = p; n->x[Nmax][0] = p;
    n->y[Nmin][0] = p; n->y[Nmax][0] = p;
}

static inline void merge(Node* n, Node const* n_a, Node const* n_b) {
    if (!n_a->x[Nmin][0]) { *n = *n_b; return; }
    if (!n_b->x[Nmin][0]) { *n = *n_a; return; }

#define INSNB(S, I, XY, OP) \
    if (n->S[0] != n_b->S[I] && n->S[1] != n_b->S[I]) { \
        if (n->S[0]->XY OP n_b->S[I]->XY) { \
            n->S[1] = n->S[0]; n->S[0] = n_b->S[I]; \
        } else if (!n->S[1] || (n->S[1]->XY OP n_b->S[I]->XY)) { \
            n->S[1] = n_b->S[I]; \
        } \
    }
#define MERGE(S, XY, OP) \
    n->S[0] = n_a->S[0]; \
    n->S[1] = n_a->S[1]; \
    INSNB(S, 0, XY, OP) \
    if (n_b->S[1]) { \
        INSNB(S, 1, XY, OP) \
    }

    MERGE(x[Nmin], x, >) MERGE(x[Nmax], x, <)
    MERGE(y[Nmin], y, >) MERGE(y[Nmax], y, <)
}

static inline i32 min_side(Node const* n) {
    i32 len = 0x7fff'ffff;

    PP p, xmin, xmax, ymin, ymax;
#define LEN(S) \
    p = n->S[0]; \
    xmin = p != n->x[Nmin][0] ? n->x[Nmin][0] : n->x[Nmin][1]; \
    xmax = p != n->x[Nmax][0] ? n->x[Nmax][0] : n->x[Nmax][1]; \
    ymin = p != n->y[Nmin][0] ? n->y[Nmin][0] : n->y[Nmin][1]; \
    ymax = p != n->y[Nmax][0] ? n->y[Nmax][0] : n->y[Nmax][1]; \
    len = min(len, max(xmax->x-xmin->x, ymax->y-ymin->y));

    LEN(x[Nmin]) LEN(x[Nmax])
    LEN(y[Nmin]) LEN(y[Nmax])
    return len;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    i32 N, Q;
    cin >> N >> Q;

    i32 M = np2(N);
    for (i32 i = 0; i < N; i++) {
        cin >> HOUSE[i].x >> HOUSE[i].y;
        init(NODES + M + i, HOUSE + i);
    }
    for (i32 i = M+N-1 &~ 1; i; i -= 2)
        merge(NODES + (i>>1), NODES + i, NODES + (i|1));

    for (i32 i = 0; i < Q; i++) {
        i32 be, en;
        cin >> be >> en;
        be = be-1-1; be += M;
        en = en-1+1; en += M;

        Node n = NODES[++be];
        while ((be ^ en) != 1) {
            if (!(be & 1)) merge(&n, &n, NODES + be + 1);
            if ( (en & 1)) merge(&n, &n, NODES + en - 1);
            be >>= 1; en >>= 1;
        }
        cout << min_side(&n) << '\n';
    }
}

static inline uint32_t np2(uint32_t x) {
    --x;
    x |= (x >>  1);
    x |= (x >>  2);
    x |= (x >>  4);
    x |= (x >>  8);
    x |= (x >> 16);
    return ++x;
}
