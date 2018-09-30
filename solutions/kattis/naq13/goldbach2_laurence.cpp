#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

bool is_prime[32007];
vector<int> primes;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    memset(is_prime, 1, sizeof(is_prime));
    for (int i = 2; i <= 32005; i++) {
        for (int j = 2; ; j++) {
            int r = i * j;
            if (r > 32005)
                break;
            is_prime[r] = false;
        }
    }
    for (int i = 2; i <= 32001; i++)
        if (is_prime[i])
            primes.emplace_back(i);

    int N;
    cin >> N;
    vector<int> a1;
    for (int i = 0; i < N; i++) {
        a1.clear();
        int x;
        cin >> x;
        for (auto p : primes) {
            if (p > x/2)
                break;
            if (is_prime[x-p])
                a1.emplace_back(p);
        }
        cout << x << " has " << a1.size() << " representation(s)\n";
        for (auto a : a1)
            cout << a << '+' << x-a << '\n';
        cout << '\n';
    }
}
