#include <cmath>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    do {
        double b1, b2, b3, b4;
        double t1, t2, t3, t4;
        cin >> b1 >> b2 >> b3 >> b4;
        cin >> t1 >> t2 >> t3 >> t4;

        double a = 3 * (b4-t4), b = 2 * (b3-t3), c = b2-t2;

        double x1 = 0, x2 = 1, x3 = 0, x4 = 0;

        for (double b2_4ac = b*b-4*a*c; b2_4ac >= 0;) {
            x3 = (-b+sqrt(b2_4ac)) / (2*a);
            if (!(0 <= x3 && x3 <= 1))
                x3 = 0;
            x4 = (-b-sqrt(b2_4ac)) / (2*a);
            if (!(0 <= x4 && x4 <= 1))
                x4 = 0;
            break;
        }

        auto f = [=](double x) {
            return b1-t1 + (b2-t2)*x + (b3-t3)*x*x + (b4-t4)*x*x*x;
        };

        double y1 = f(x1), y2 = f(x2), y3 = f(x3), y4 = f(x4);

        double _max = max(y1, max(y2, max(y3, y4)));
        double _min = min(y1, min(y2, min(y3, y4)));

        cout << _max - _min << endl;

        cin.get(); cin.get();
    } while (cin.good());
}
