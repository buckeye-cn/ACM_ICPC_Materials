#include <iostream>
#include <unordered_set>

using namespace std;

constexpr uint64_t x2018 = 2018l << 32;
constexpr uint64_t y2018 = 2018l;
constexpr uint64_t x1118 = 1118l << 32;
constexpr uint64_t y1118 = 1118l;
constexpr uint64_t x1680 = 1680l << 32;
constexpr uint64_t y1680 = 1680l;

constexpr uint64_t p01 = 0 + x2018;
constexpr uint64_t p02 = 0 - x2018;
constexpr uint64_t p03 = 0 + y2018;
constexpr uint64_t p04 = 0 - y2018;
constexpr uint64_t p05 = 0 + x1118 + y1680;
constexpr uint64_t p06 = 0 + x1118 - y1680;
constexpr uint64_t p07 = 0 - x1118 + y1680;
constexpr uint64_t p08 = 0 - x1118 - y1680;
constexpr uint64_t p09 = 0 + x1680 + y1118;
constexpr uint64_t p10 = 0 + x1680 - y1118;
constexpr uint64_t p11 = 0 - x1680 + y1118;
constexpr uint64_t p12 = 0 - x1680 - y1118;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    uint32_t N;
    cin >> N;

    unordered_set<uint64_t> points = {};
    for (uint32_t i = 0; i < N; i++) {
        uint64_t x, y;
        cin >> x >> y;
        points.insert((x << 32) + y);
    }

    uint32_t c = 0;
    for (const uint64_t p : points) {
        c += points.count(p + p01);
        c += points.count(p - p02);
        c += points.count(p + p03);
        c += points.count(p - p04);
        c += points.count(p + p05);
        c += points.count(p + p06);
        c += points.count(p - p07);
        c += points.count(p - p08);
        c += points.count(p + p09);
        c += points.count(p + p10);
        c += points.count(p - p11);
        c += points.count(p - p12);
    }
    cout << c / 2 << "\n";
}
