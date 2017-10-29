// https://open.kattis.com/problems/throwns

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int n, m;
vector<int> pos;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;
    pos.push_back(0);

    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;

        if (s == "undo") {
            int j;
            cin >> j;

            for (int k = 0; k < j; ++k) {
                pos.pop_back();
            }
        } else {
            int j = stol(s);
            pos.push_back(pos.back() + j);
        }
    }

    cout << (pos.back() % n + n) % n << endl;

    return 0;
}
