// https://open.kattis.com/problems/tornbygge

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

    int prev = 0;
    int result = 0;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        result += prev < x;
        prev = x;
    }

    cout << result << endl;

    return 0;
}
