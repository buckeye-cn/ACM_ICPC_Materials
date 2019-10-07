#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long M, N;
    cin >> M >> N;

    long g = __gcd(M, N);

    M /= g;
    N /= g;

    if ((M % 2 == 0) != (N % 2 == 0)) {
        cout << 0 << endl;
    } else {
        cout << g << endl;
    }
}
