#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        pair<int, int> v[5];

        while (true) {
            int day;
            cin >> day;

            if (day <= 75) {
                cout << (day % 15) + 1 << ' ' << 100 - day / 15 << endl;
            } else if (day <= 80) {
                cout << (day % 5) + 16 << ' ' << 0 << endl;

                cin >> v[day % 5].first;
                v[day % 5].second = (day % 5) + 16;

                for (int i = 0; i < v[day % 5].first; ++i) {
                    int p;
                    cin >> p;
                }
            } else if (day < 100) {
                if (v[3] > v[4]) swap(v[3], v[4]);
                if (v[2] > v[3]) swap(v[2], v[3]);
                if (v[1] > v[2]) swap(v[1], v[2]);
                if (v[0] > v[1]) swap(v[0], v[1]);

                cout << v[1].second << ' ' << day << endl;

                v[1].first += 1;
            } else {
                cout << v[0].second << ' ' << 100 << endl;

                break;
            }
        }
    }

    return 0;
}
