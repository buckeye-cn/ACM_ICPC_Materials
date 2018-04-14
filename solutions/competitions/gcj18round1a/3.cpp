#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

double w[200];
double h[200];
double r_min[200];
double r_max[200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        // cout << "Case #" << n_case << ": ";

        int n;
        double p;
        cin >> n >> p;

        for (int i = 0; i < n; ++i) {
            cin >> w[i] >> h[i];
        }

        double pp = p;

        for (int i = 0; i < n; ++i) {
            pp -= (w[i] + h[i]) * 2;

            r_min[i] = min(w[i], h[i]) * 2;
            r_max[i] = sqrt(w[i] * w[i] + h[i] * h[i]) * 2;
        }

        set<pair<double, double>> s[2];
        s[0].insert({0, 0});

        for (int i = 0; i < n; ++i) {
            for (auto j: s[0]) {
                s[1].insert(j);
                if (j.first + r_min[i] <= pp) {
                    s[1].insert({
                        j.first + r_min[i],
                        min(j.second + r_max[i], pp)
                    });
                }
            }

            pair<double, double> last = {0, 0};

            s[0].clear();

            for (auto j: s[1]) {
                if (last.second < j.first) {
                    s[0].insert(last);
                    last = j;
                } else {
                    last.second = max(last.second, j.second);
                }
            }

            s[0].insert(last);
        }

        printf("Case #%d: %.10f\n", n_case, p - pp + s[0].rbegin()->second);
    }

    return 0;
}
