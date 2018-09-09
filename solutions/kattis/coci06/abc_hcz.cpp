// https://open.kattis.com/problems/abc

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

    int data[3];
    cin >> data[0] >> data[1] >> data[2];

    if (data[0] > data[1]) swap(data[0], data[1]);
    if (data[1] > data[2]) swap(data[1], data[2]);
    if (data[0] > data[1]) swap(data[0], data[1]);

    string s;
    cin >> s;

    cout << data[s[0] - 'A'] << ' '
        << data[s[1] - 'A'] << ' '
        << data[s[2] - 'A'] << endl;

    return 0;
}
