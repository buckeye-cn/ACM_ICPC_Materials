// https://open.kattis.com/problems/researchproductivityindex

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    double p[n];

    for (int i = 0; i < n; ++i) {
        int pp;
        cin >> pp;

        p[i] = 0.01 * pp;

        for (int j = i - 1; j >= 0; --j) {
            if (p[j] < p[j + 1]) {
                swap(p[j], p[j + 1]);
            }
        }
    }

    double dist[n + 1];
    double best = 0;

    dist[0] = 1;

    for (int i = 0; i < n; ++i) {
        dist[i + 1] = 0;

        for (int j = i + 1; j > 0; --j) {
            dist[j] = dist[j - 1] * p[i] + dist[j] * (1 - p[i]);
        }

        dist[0] = dist[0] * (1 - p[i]);

        double total = 0;

        for (int j = 1; j <= i + 1; ++j) {
            total += pow(j, double(j) / (i + 1)) * dist[j];
        }

        if (best < total) {
            best = total;
        }
    }

    cout << best << endl;

    return 0;
}
