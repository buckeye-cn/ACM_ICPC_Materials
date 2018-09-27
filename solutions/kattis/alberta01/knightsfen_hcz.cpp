// https://open.kattis.com/problems/knightsfen

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

#define SHIFT(x, y) ((x) * 10 + (y) * 2)

using namespace std;

unordered_map<long, int> m;

void dfs(int depth, long data, int sp_x, int sp_y) {
    if (sp_x < 0 || sp_x >= 5 || sp_y < 0 || sp_y >= 5) {
        return;
    }

    if (depth == 11) {
        return;
    }

    if (m.find(data) == m.end()) {
        m[data] = depth;
    } else if (m[data] <= depth) {
        return;
    } else {
        m[data] = depth;
    }

    long data_1;

    auto rec = [&](int dx, int dy) {
        data_1 = data;
        data_1 &= ~(3l << SHIFT(sp_x + dx, sp_y + dy));
        data_1 |= ((data >> SHIFT(sp_x + dx, sp_y + dy)) & 0x03) << SHIFT(sp_x, sp_y);
        return dfs(depth + 1, data_1, sp_x + dx, sp_y + dy);
    };

    rec(2, 1);
    rec(1, 2);
    rec(-2, 1);
    rec(-1, 2);
    rec(2, -1);
    rec(1, -2);
    rec(-2, -1);
    rec(-1, -2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    dfs(0, 375575165970090l, 2, 2);

    int n;
    cin >> n;

    cin.get();

    for (int i = 0; i < n; ++i) {
        long data = 0;
        int sp_x;
        int sp_y;

        for (int j = 0; j < 5; ++j) {
            char s[6];
            cin.getline(s, 6);

            for (int k = 0; k < 5; ++k) {
                if (s[k] == ' ') {
                    sp_x = j;
                    sp_y = k;
                } else if (s[k] == '0') {
                    data |= 1l << (SHIFT(j, k) + 0);
                } else if (s[k] == '1') {
                    data |= 1l << (SHIFT(j, k) + 1);
                }
            }
        }

        if (m.find(data) == m.end()) {
            m[data] = 11;
        }

        if (m[data] == 11) {
            cout << "Unsolvable in less than 11 move(s)." << endl;
        } else {
            cout << "Solvable in " << m[data] << " move(s)." << endl;
        }
    }

    return 0;
}
