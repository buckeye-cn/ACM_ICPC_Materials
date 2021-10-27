// https://open.kattis.com/problems/jumbojavelin

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

    int n;
    cin >> n;

    int s = 1 - n;

    for (int i = 0; i < n; ++i) {
        int l;
        cin >> l;

        s += l;
    }

    cout << s << endl;

    return 0;
}
