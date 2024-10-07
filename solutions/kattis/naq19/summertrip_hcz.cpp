// https://open.kattis.com/problems/summertrip

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

    string s;
    cin >> s;

    int total = 0;

    for (char i = 'a'; i <= 'z'; ++i) {
        for (char j = 'a'; j <= 'z'; ++j) {
            if (i == j) continue;

            bool inside = false;

            for (char c: s) {
                if (inside && c == j) {
                    total += 1;
                    inside = false;
                } else if (!inside && c == i) {
                    inside = true;
                }
            }
        }
    }

    cout << total << endl;

    return 0;
}
