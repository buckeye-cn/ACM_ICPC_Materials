#include <cfloat>
#include <cmath>
#include <iostream>

using namespace std;

bool feq(double a, double b) {
    return (abs(a-b) < 1e-7);
}

int main() {
    int n_lines;
    cin >> n_lines;

    for (int _i = 0; _i < n_lines; _i++) {
        double l1, a1, l2, a2, lt, at;
        cin >> l1 >> a1 >> l2 >> a2 >> lt >> at;

        if (feq(a1/l1, a2/l2) && feq(a2/l2, at/lt)) {
            int sol = 0, x = 0, y = 0;
            for (int i = 1; i < 10000; i++) {
                double j = (lt - l1 * i) / l2;
                if (j > 1.-1e-7 && feq(j, round(j))) {
                    sol += 1;
                    x = i;
                    y = round(j);
                }
            }
            if (sol == 1) {
                cout << x << " " << y << endl;
            } else {
                cout << "?" << endl;
            }
        } else {
            double l1_a1 = l1 / a1;
            double a2_1 = a2 * l1_a1;
            double at_1 = at * l1_a1;

            double y = (at_1 - lt) / (a2_1 - l2);
            double x = (lt - y * l2) / l1;

            if (x > 1.-1e-7 && y > 1.-1e-7 && feq(x, round(x)) && feq(y, round(y)) && !isnan(x) && !isnan(y)) {
                cout << round(x) << " " << round(y) << endl;
            } else {
                cout << "?" << endl;
            }
        }
    }
}
