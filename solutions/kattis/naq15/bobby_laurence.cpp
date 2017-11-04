#include <cmath>
#include <iostream>

using namespace std;

const float factorial[11] = {
    1.f,
    1.f,
    2.f,
    6.f,
    24.f,
    120.f,
    720.f,
    5040.f,
    40320.f,
    362880.f,
    3628800.f,
};

inline float choose(uint16_t n, uint16_t k) {
    return factorial[n] / factorial[k] / factorial[n-k];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint32_t N;
    cin >> N;

    for (uint32_t _i = 0; _i < N; _i++) {
        float r, s, w;
        uint16_t x, y;
        cin >> r >> s >> x >> y >> w;

        float p_win = (s - r + 1.f) / s;

        if (p_win == 0.f) {
            cout << "no\n";
        } else {
            float p = 0.f;
            for (uint16_t i = x; i <= y; i++) {
                p += choose(y, i) * pow(p_win, i) * pow(1.f-p_win, y-i);
            }
            if (p * w > 1.f) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        }
    }
}
