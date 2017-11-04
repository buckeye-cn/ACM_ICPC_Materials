#include <cmath>
#include <iostream>

using namespace std;

double d, s;

double a0 = 0, a1 = 1e10;
double a = 5e9;
double x;

inline double f(double a) {
    x = d / (a * 2.f);
    return a + s - a * (exp(x) + exp(-x)) / 2.f;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> d >> s;

    while (1) {
        a = (a0 + a1) / 2.f;
        double y = f(a);
        if (y > 1e-7)
            a1 = a;
        else if (y < -1e-7)
            a0 = a;
        else
            break;
    }

    cout << a * (exp(x) - exp(-x)) << endl;
}
