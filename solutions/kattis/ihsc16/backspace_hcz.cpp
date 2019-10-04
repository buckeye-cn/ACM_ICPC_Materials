// https://open.kattis.com/problems/backspace

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char buf[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin.getline(buf, 1000001);

    int n1 = 0;
    int n2 = 0;
    for (; buf[n1]; ++n1) {
        if (buf[n1] == '<') {
            n2 -= 1;
        } else {
            buf[n2++] = buf[n1];
        }
    }

    cout.write(buf, n2);
    cout << endl;

    return 0;
}
