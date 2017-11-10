// https://open.kattis.com/problems/mixedfractions

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

    while (true) {
        int a, b;
        cin >> a >> b;

        if (!a && !b) {
            return 0;
        }

        cout << a / b << ' ' << a % b << " / " << b << endl;
    }
}
