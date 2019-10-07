#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N;
    cin >> N;

    vector<long> nums;
    for (long i = 0; i < N; i++) {
        long x;
        cin >> x;
        nums.push_back(x);
    }

    double maxx = -10e9;

    {
        double sum = 0, avg = 0, c = 0;
        for (long i = N - 1; i >= 0; i--) {
            c += 1;
            sum += nums[i];
            avg  = sum / c;
            maxx = max(maxx, avg);
        }
    }
    {
        double sum = 0, avg = 0, c = 0;
        for (long i = 0; i < N - 1; i++) {
            c += 1;
            sum += nums[i];
            avg  = sum / c;
            maxx = max(maxx, avg);
        }
    }

    maxx = max(maxx, 0.0);

    cout << maxx << endl;
}
