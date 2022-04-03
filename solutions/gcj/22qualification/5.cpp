#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int pval[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        int n, k;
        cin >> n >> k;

        memset(pval, 0, sizeof(pval));

        for (int i = 0; i <= k; ++i) {
            int r, p;
            cin >> r >> p;

            pval[r] = p;

            if (i == k) {
                long tot = 0;
                long cnt = 0;

                for (int j = 1; j <= n; ++j) {
                    if (pval[j]) {
                        tot += pval[j];
                        cnt += 1;
                    }
                }

                for (int j = 1; j <= n; ++j) {
                    if (!pval[j]) {
                        for (int k = 0; k < 100; ++k) {
                            int rep = rand() % n + 1;

                            if (pval[rep] && pval[rep] * cnt <= 10 * tot) {
                                tot += pval[rep];
                                cnt += 1;
                                break;
                            }
                        }
                    }
                }


                cout << "E " << tot / 2 << endl;
            } else if ((i & 1) == 0 && i < k / 5) {
                cout << 'W' << endl;
            } else {
                int next;

                for (int j = 0; j < 100; ++j) {
                    next = rand() % n + 1;

                    if (!pval[next]) break;
                }

                cout << "T " << next << endl;
            }
        }
    }

    return 0;
}
