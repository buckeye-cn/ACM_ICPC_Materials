#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int a[1000];
int b[1000];
int h[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }

    h[0] = 1;
    int max = 1;

    for (int i = 1; i <= 1000; ++i) {
        for (int j = 0; j < n; ++j) {
            if (h[a[j]] == i) {
                h[b[j]] = i + 1;
                max = i;
            }
        }
    }

    cout << max << endl;

    return 0;
}
