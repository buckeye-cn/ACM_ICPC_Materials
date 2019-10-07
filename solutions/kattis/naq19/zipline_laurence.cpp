#include <bits/stdc++.h>

using namespace std;

inline void testcase() {
    double w, g, h, r;
    cin >> w >> g >> h >> r;

    double maxx = 0, minn = 0;

    minn = sqrt(w * w + (g - h) * (g - h));

    if (g == h && h == r) {
        maxx = minn;
    } else {
        auto solve = [=](double i) { // r min
            return sqrt(i * i + (g - r) * (g - r)) + sqrt((w - i) * (w - i) + (h - r) * (h - r));
        };
        double i = ((g - r) * w) / (h + g - 2.0 * r);
        maxx     = solve(i);
    }

    cout << minn << ' ' << maxx << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(30);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        testcase();
    }
}
