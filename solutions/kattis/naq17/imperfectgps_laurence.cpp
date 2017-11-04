#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

static double dist(double p1[2], double p2[2]) {
    return sqrt(pow(p2[0] - p1[0], 2.) + pow(p2[1] - p1[1], 2.));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    unsigned int n;
    double gps_dt;
    cin >> n >> gps_dt;

    double pos[101][2] = {};
    double ts[101] = {};

    for (unsigned int i = 1; i <= n; i++)
        cin >> pos[i][0] >> pos[i][1] >> ts[i];

    double t = gps_dt;
    double gps_lastp[2] = { pos[1][0], pos[1][1] };
    double tot_gps = 0;

    while (1) {
        unsigned int i;
        for (i = 1; i <= n; i++)
            if (ts[i] >= t)
                break;

        double dp[2] = { pos[i][0] - pos[i-1][0], pos[i][1] - pos[i-1][1] };
        double dt = (t - ts[i-1]) / (ts[i] - ts[i-1]);

        double gps_newp[2] = {
            pos[i-1][0] + dt * dp[0],
            pos[i-1][1] + dt * dp[1],
        };
        tot_gps += dist(gps_newp, gps_lastp);
        gps_lastp[0] = gps_newp[0];
        gps_lastp[1] = gps_newp[1];

        if (t == ts[n])
            break;

        if (t + gps_dt > ts[n])
            t = ts[n];
        else
            t += gps_dt;
    }

    double tot_rel = 0;
    for (unsigned int i = 2; i <= n; i++)
        tot_rel += dist(pos[i], pos[i-1]);

    if (gps_dt > ts[n])
        tot_gps = dist(pos[n], pos[1]);

    cout << abs(tot_rel - tot_gps) / tot_rel * 100. << endl;
}
