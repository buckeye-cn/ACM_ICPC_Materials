// https://open.kattis.com/problems/snapperhard

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

    cin.get();

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int n, k;
        cin >> n >> k;

        cout << ((k + 1) >> n << n == k + 1 ? "ON" : "OFF") << endl;
    }

    return 0;
}
