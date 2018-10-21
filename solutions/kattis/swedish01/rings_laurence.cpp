#include <bits/stdc++.h>

using namespace std;

struct C {
    double x, y, r;

    bool isec(C const& other) const {
        auto d = sqrt( pow(x-other.x, 2) + pow(y-other.y, 2) );
        return abs(r-other.r) < d && d < r+other.r;
    }
} circles[103];

int N;
bool checked[103];

int dfs(int i) {
    int c = 1;
    for (int j = 0; j < N; j++) {
        if (!checked[j]) {
            if (circles[i].isec(circles[j])) {
                checked[j] = true;
                c += dfs(j);
            }
        }
    }
    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (;;) {
        cin >> N;
        if (N == -1)
            break;
        memset(checked, 0, sizeof(checked));
        for (int i = 0; i < N; i++)
            cin >> circles[i].x >> circles[i].y >> circles[i].r;

        int _max = 0;

        for (int i = 0; i < N; i++) {
            if (!checked[i]) {
                checked[i] = true;
                _max = max(_max, dfs(i));
            }
        }

        cout << "The largest component contains " << _max << (_max > 1 ? " rings.\n" : " ring.\n");
    }
}
