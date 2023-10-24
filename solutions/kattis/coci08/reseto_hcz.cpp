// https://open.kattis.com/problems/reseto

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool visited[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, k;
    cin >> n >> k;

    for (int i = 2; true; ++i) {
        if (visited[i]) continue;

        for (int j = i; j <= n; j += i) {
            if (visited[j]) continue;

            visited[j] = true;
            k -= 1;

            if (!k) {
                cout << j << endl;

                return 0;
            }
        }
    }
}
