#include <iostream>

using namespace std;

int x[100000];
int y[100000];
int yy[2][100000];

int main() {
    int n;
    int nn[2];

    cin >> n;

    nn[0] = n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    int min_x = x[0];
    int max_x = x[0];

    for (int i = 0; i < n; ++i) {
        min_x = min(min_x, x[i]);
        max_x = max(max_x, x[i]);

        yy[0][i] = y[i];
    }

    int mode = 0;
    int remain = n / 2;
    int done = 0;

    while (!done) {
        int total = nn[mode];
        int mid = yy[mode][rand() % total];

        nn[0] = 0;
        nn[1] = 0;
        done = 1;

        for (int i = 0; i < total; ++i) {
            int new_mode = yy[mode][i] > mid || (yy[mode][i] == mid && rand() % 2);

            done &= yy[mode][i] == mid;

            yy[new_mode][nn[new_mode]] = yy[mode][i];
            nn[new_mode] += 1;
        }

        if (nn[0] <= remain) {
            mode = 1;
            remain -= nn[0];
        } else {
            mode = 0;
        }
    }

    long result = max_x - min_x;

    for (int i = 0; i < n; ++i) {
        result += abs(y[i] - yy[mode][0]);
    }

    cout << result << endl;

    return 0;
}
