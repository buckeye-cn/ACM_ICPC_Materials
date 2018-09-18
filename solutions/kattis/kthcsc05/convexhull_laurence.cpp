#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

struct Pt {
    int x, y;

    bool operator==(Pt const& o) const {
        return x == o.x && y == o.y;
    }

    bool operator<(Pt const& o) const {
        return (x < o.x) || (x == o.x && y < o.y);
    }
};

inline bool right_turn(Pt p1, Pt p2, Pt p) {
    return ((p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x)) > 0;
}

array<Pt, 10023> pts;
array<Pt, 10023> cv;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (;;) {
        int N;
        cin >> N;
        if (N == 0)
            break;
        for (int i = 0; i < N; i++)
            cin >> pts[i].x >> pts[i].y;
        sort(pts.begin(), pts.begin()+N);
        N = distance(pts.begin(), unique(pts.begin(), pts.begin()+N));

        if (N > 2) {
            int cc = 0, min_cc = 2;
            for (int i = 0; i < N; i++) {
                while (cc >= min_cc && !right_turn(cv[cc-2], cv[cc-1], pts[i]))
                    cc--;
                cv[cc++] = pts[i];
            }
            min_cc = cc + 1;
            for (int i = N-2; i >= 0; i--) {
                while (cc >= min_cc && !right_turn(cv[cc-2], cv[cc-1], pts[i]))
                    cc--;
                cv[cc++] = pts[i];
            }
            cc--;
            cout << cc << '\n';
            for (int i = cc-1; i >= 0; i--)
                cout << cv[i].x << ' ' << cv[i].y << '\n';
        } else {
            cout << N << '\n';
            for (int i = 0; i < N; i++)
                cout << pts[i].x << ' ' << pts[i].y << '\n';
        }
    }
}
