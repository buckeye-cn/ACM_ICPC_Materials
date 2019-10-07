#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double ta[101][101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N;
    cin >> N;

    vector<double> pp;
    for (int i = 0; i < N; i++) {
        int p;
        cin >> p;
        pp.push_back((double)p / 100.0);
    }

    sort(pp.begin(), pp.end(), greater<double>());

    ta[1][0] = 1.0 - pp[0];
    ta[1][1] = pp[0];

    double index = ta[1][1];

    for (int i = 2; i <= N; i++) {
        double p      = pp[i - 1];
        ta[i][0]      = ta[i - 1][0] * (1.0 - p);
        double _index = 0.0;
        for (int j = 1; j <= i; j++) {
            ta[i][j]  = ta[i - 1][j - 1] * p + ta[i - 1][j] * (1.0 - p);
            double ri = pow((double)j, (double)j / (double)i);
            _index += ta[i][j] * ri;
        }
        index = max(index, _index);
    }

    cout << index << endl;
}
