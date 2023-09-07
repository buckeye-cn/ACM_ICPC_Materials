// https://open.kattis.com/problems/iforaneye

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

    pair<char, string> rule[] {
        {'@', "at"},
        {'&', "and"},
        {'1', "one"},
        {'1', "won"},
        {'2', "to"},
        {'2', "too"},
        {'2', "two"},
        {'4', "for"},
        {'4', "four"},
        {'b', "bea"},
        {'b', "be"},
        {'b', "bee"},
        {'c', "sea"},
        {'c', "see"},
        {'i', "eye"},
        {'o', "oh"},
        {'o', "owe"},
        {'r', "are"},
        {'u', "you"},
        {'y', "why"},
        {'@', "At"},
        {'&', "And"},
        {'1', "One"},
        {'1', "Won"},
        {'2', "To"},
        {'2', "Too"},
        {'2', "Two"},
        {'4', "For"},
        {'4', "Four"},
        {'B', "Bea"},
        {'B', "Be"},
        {'B', "Bee"},
        {'C', "Sea"},
        {'C', "See"},
        {'I', "Eye"},
        {'O', "Oh"},
        {'O', "Owe"},
        {'R', "Are"},
        {'U', "You"},
        {'Y', "Why"},
    };

    int n;
    cin >> n;
    cin.get();

    for (int i = 0; i < n; ++i) {
        char buf[256];
        cin.getline(buf, sizeof(buf));

        for (int j = 0; buf[j]; ++j) {
            int best = -1;
            int best_len = 0;

            for (int k = 0; k < sizeof(rule) / sizeof(rule[0]); ++k) {
                int len = rule[k].second.size();

                if (string(buf + j, len) == rule[k].second && best_len < len) {
                    best = k;
                    best_len = len;
                }
            }

            if (best >= 0) {
                cout << rule[best].first;
                j += best_len - 1;
            } else {
                cout << buf[j];
            }
        }

        cout << endl;
    }

    return 0;
}
