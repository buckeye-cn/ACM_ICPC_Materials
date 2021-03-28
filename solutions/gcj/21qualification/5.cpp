#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <iostream>

using namespace std;

char c[100][10000];
int tot_i[100];
int tot_j[10000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t, p;
    cin >> t >> p;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        memset(tot_i, 0, sizeof(tot_i));
        memset(tot_j, 0, sizeof(tot_j));

        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 10000; ++j) {
                cin >> c[i][j];

                if (c[i][j] == '1') {
                    tot_i[i] += 1;
                    tot_j[j] += 1;
                }
            }
        }

        map<int, double> scores;

        for (int i = 0; i < 100; ++i) {
            double s1 = 0;
            double s2 = 0;

            for (int j = 0; j < 10000; ++j) {
                double d = 0.0003 * tot_i[i] - 0.03 * tot_j[j];

                if (c[i][j] == '1') {
                    s1 += log(1 / (1 + exp(d)));
                } else {
                    s2 += log(1 / (1 + exp(-d)));
                }
            }

            double score = pow(-s1, 0.3) + pow(-s2, 0.3);

            scores.insert({tot_i[i] * 100 + i, score});
        }

        int i = 0;
        int ii[100];
        double ss[100];

        for (auto &pair: scores) {
            ii[i] = pair.first % 100;
            ss[i] = pair.second;
            i += 1;
        }

        int best = 0;
        double best_delta = 0;

        for (int i = 0; i < 100; ++i) {
            int ic = min(max(i, 1), 98);

            double sum_ss = 0;

            for (int j = ic - 1; j <= ic + 1; ++j) {
                sum_ss += ss[j];
            }

            double delta = ss[i] * 3 - sum_ss;

            if (tot_i[ii[i]] >= 5000 && best_delta < delta) {
                best = ii[i];
                best_delta = delta;
            }
        }

        cout << best + 1 << endl;
    }

    return 0;
}
