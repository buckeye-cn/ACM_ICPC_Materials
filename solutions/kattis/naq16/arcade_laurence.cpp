#include <iostream>
#include <utility>

#define W 34

using namespace std;

static unsigned N;

static float payouts[W][W] = {};
static float prob[W][W][5] = {};

static float fall[W][W] = {};
static float pass[2][W][W] = {};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(6);

    cin >> N;

    for (unsigned i = 1; i <= N; i++)
        for (unsigned j = 1; j <= i; j++)
            cin >> payouts[i][j];

    for (unsigned i = 1; i <= N; i++)
        for (unsigned j = 1; j <= i; j++)
            cin >> prob[i][j][0]
                >> prob[i][j][1]
                >> prob[i][j][2]
                >> prob[i][j][3]
                >> prob[i][j][4];

    unsigned p1 = 0;
    unsigned p2 = 1;

    pass[p1][1][1] = 1.f;

    for (unsigned _i = 0; _i < 6000; _i++) {
        for (unsigned i = 1; i <= N; i++) {
            for (unsigned j = 1; j <= i; j++) {
                pass[p2][i-1][j-1] += pass[p1][i][j] * prob[i][j][0];
                pass[p2][i-1][j  ] += pass[p1][i][j] * prob[i][j][1];
                pass[p2][i+1][j  ] += pass[p1][i][j] * prob[i][j][2];
                pass[p2][i+1][j+1] += pass[p1][i][j] * prob[i][j][3];
                fall[i][j]         += pass[p1][i][j] * prob[i][j][4];
                pass[p1][i][j] = 0.f;
            }
        }
        swap(p1, p2);
    }

    float tf = 0.f;
    float e = 0.f;
    for (unsigned i = 1; i <= N; i++) {
        for (unsigned j = 1; j <= i; j++) {
            tf += fall[i][j];
            e += fall[i][j] * payouts[i][j];
        }
    }
    e /= tf;
    cout << e << "\n";
}
