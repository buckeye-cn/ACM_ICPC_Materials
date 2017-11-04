#include <cmath>
#include <iostream>

using namespace std;

inline float factorial(uint16_t x) {
    switch (x) {
        case 0 : return 1;
        case 1 : return 1;
        case 2 : return 2;
        case 3 : return 6;
        case 4 : return 24;
        case 5 : return 120;
        case 6 : return 720;
        case 7 : return 5040;
        case 8 : return 40320;
        case 9 : return 362880;
        case 10: return 3628800;
        case 11: return 39916800;
        default: return 0;
    }
}

inline float choose(uint16_t n, uint16_t k) {
    return factorial(n) / factorial(k) / factorial(n-k);
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
            for (uint8_t i = x; i <= y; i++) {
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
