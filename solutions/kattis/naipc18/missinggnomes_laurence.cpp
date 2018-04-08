#include <iostream>

using namespace std;

bool na[100003] = {};
uint32_t ns[100003] = {};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint32_t N, M;
    cin >> N >> M;

    for (uint32_t i = 0; i < M; i++) {
        uint32_t n;
        cin >> n;
        na[n] = true;
        ns[i] = n;
    }

    uint32_t ina = 0, ins = 0;

    while (na[++ina]) {} // init

    for (uint32_t i = 0; i < N; i++) {
        uint32_t n1 = (ina <= N) ? ina : -1, n2 = (ins < M) ? ns[ins] : -1;
        if (n1 < n2) {
            while (na[++ina]) {}
            cout << n1 << '\n';
        } else {
            ins++;
            cout << n2 << '\n';
        }
    }
}
