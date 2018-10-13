#include <iostream>

using namespace std;

bool blink1[10003];
bool blink2[10003];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int p, q, s;
    cin >> p >> q >> s;

    for (int i = 1; i*p < s+3; i++) {
        blink1[i*p] = 1;
    }
    for (int i = 1; i*q < s+3; i++) {
        blink2[i*q] = 1;
    }
    for (int i = 1; i <= s; i++) {
        if (blink1[i] == 1 && blink2[i] == 1) {
            cout << "yes\n";
            return 0;
        }
    }
    cout << "no\n";
    return 0;
}
