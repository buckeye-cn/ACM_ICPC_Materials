// https://open.kattis.com/problems/cardtrick2

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

    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;

        int top = 0;
        int cards[n];

        memset(cards, 0, sizeof(cards));

        for (int j = 1; j <= n; ++j) {
            int discard = j;

            while (discard) {
                if (!cards[top]) discard -= 1;

                top += 1;
                top %= n;
            }

            while (cards[top]) {
                top += 1;
                top %= n;
            }

            cards[top] = j;

            top += 1;
            top %= n;
        }

        cout << cards[0];
        for (int j = 1; j < n; ++j) {
            cout << ' ' << cards[j];
        }
        cout << endl;
    }

    return 0;
}
