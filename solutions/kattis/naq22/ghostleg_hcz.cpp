// https://open.kattis.com/problems/ghostleg

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int nums[101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        nums[i] = i;
    }

    for (int i = 1; i <= m; ++i) {
        int a;
        cin >> a;

        swap(nums[a], nums[a + 1]);
    }

    for (int i = 1; i <= n; ++i) {
        cout << nums[i] << endl;
    }

    return 0;
}
