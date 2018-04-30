#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ":";

        int n;
        cin >> n;

        int tot = 0;
        set<pair<int, char>> remain;

        for (int i = 0; i < n; ++i) {
            int p;
            cin >> p;

            tot += p;
            remain.insert({p, 'A' + i});
        }

        while (remain.rbegin()->first) {
            pair<int, char> first = *remain.rbegin();
            remain.erase(first);

            pair<int, char> second = *remain.rbegin();
            remain.erase(second);

            if (first.first > second.first || tot == 3) {
                cout << ' ' << first.second;
                first.first -= 1;
                tot -= 1;
            } else {
                cout << ' ' << first.second << second.second;
                first.first -= 1;
                second.first -= 1;
                tot -= 2;
            }

            remain.insert(first);
            remain.insert(second);
        }

        cout << endl;
    }

    return 0;
}
