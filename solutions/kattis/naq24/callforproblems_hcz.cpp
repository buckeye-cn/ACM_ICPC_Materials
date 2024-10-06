// https://open.kattis.com/problems/callforproblems

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

    int count = 0;

    for (int i = 0; i < n; ++i) {
        int d;
        cin >> d;

        count += d & 1;
    }

    cout << count << endl;

    return 0;
}
