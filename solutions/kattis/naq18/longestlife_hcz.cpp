// https://open.kattis.com/problems/longestlife

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

double t[100000];
double v[100000];
double age[100001];
int jump[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    double n;
    int p;
    double c;
    cin >> n >> p >> c;

    int pp = 1;

    v[0] = 1;
    for (int i = 0; i < p; ++i) {
        double x, y;
        cin >> t[pp] >> x >> y;

        v[pp] = y / x;

        if (v[pp] < v[pp - 1]) {
            pp += 1;
        }
    }

    double result = n;

    for (int i = 1; i < pp; ++i) {
        age[i] = t[i] + c;
        jump[i] = i - 1;

        for (int j = i; j; j = jump[j]) {
            int k = jump[j];
            double v_age = age[k] + (t[i] - t[k]) * v[k];

            if (age[i] > v_age + c) {
                age[i] = v_age + c;
            } else if (age[i] <= v_age) {
                jump[j] = jump[k];
            }
        }

        result = max(result, (n - age[i]) / v[i] + t[i]);
    }

    cout << result << endl;

    return 0;
}
