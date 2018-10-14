#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string em, key;
    cin >> em >> key;

    for (size_t i = 0; i < em.length(); i++) {
        int c = (em[i] - key[i] + 26) % 26 + 'A';
        key.push_back((char)c);
        cout << (char)c;
    }
    cout << '\n';
}
