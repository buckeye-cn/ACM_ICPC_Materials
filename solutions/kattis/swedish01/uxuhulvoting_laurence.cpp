#include <array>
#include <iostream>

using namespace std;

constexpr array<array<int8_t, 3>, 8> JUMP {{
    {{ 1, 2, 4 }},
    {{ 0, 3, 5 }},
    {{ 0, 3, 6 }},
    {{ 1, 2, 7 }},
    {{ 0, 5, 6 }},
    {{ 1, 4, 7 }},
    {{ 2, 4, 7 }},
    {{ 3, 5, 6 }},
}};

array<array<int8_t, 8>, 103> pref;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int M;
        cin >> M;

        for (int vi = 0; vi < M; vi++) {
            for (int i = 0; i < 8; i++) {
                cin >> pref[vi][i];
                pref[vi][i]--;
            }
        }

        array<int8_t, 8> outcome {};
        array<int8_t, 8> outcome_p {};
        for (int vi = M-1; vi >= 0; vi--) {
            for (int ps = 0; ps < 8; ps++) {
                int8_t bestp = 100, bestoc = -1;
                for (auto to : JUMP[ps]) {
                    int8_t oc = (vi < M-1) ? outcome_p[to] : to;
                    if (pref[vi][oc] < bestp) {
                        bestp = pref[vi][oc];
                        bestoc = oc;
                    }
                }
                outcome[ps] = bestoc;
            }
            outcome_p = outcome;
        }

        auto oc = outcome[0];
        cout << ((oc & 4) ? 'Y' : 'N');
        cout << ((oc & 2) ? 'Y' : 'N');
        cout << ((oc & 1) ? 'Y' : 'N');
        cout << endl;
    }
}
