// https://ecna16.kattis.com/problems/ecna16.waif
// not AC yet

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n, m, p;

int child_sum[128];
int child_want[128][128];
int toy_cat[128];

int child_order[128];

bool used[128];
int cat_limit[128];
int filled;
int best;

double complexity;
double c;

void search(int d) {
    if (rand() > c * RAND_MAX) return;
    if (d > n) {
        if (best < filled) best = filled;
    } else {
        int child = child_order[d];

        for (int i = 1; i <= child_sum[child]; ++i) {
            int toy = child_want[child][i];
            int cat = toy_cat[toy];

            if (used[toy]) continue;
            if (!cat_limit[cat]) continue;

            used[toy] = true;
            cat_limit[cat] -= 1;
            filled += 1;
            search(d + 1);
            filled -= 1;
            cat_limit[cat] += 1;
            used[toy] = false;
        }

        search(d + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.precision(10);

    cin >> n >> m >> p;

    for (int child = 1; child <= n; ++child) {
        cin >> child_sum[child];
        for (int i = 1; i <= child_sum[child]; ++i) {
            cin >> child_want[child][i];
        }
        complexity += log(child_sum[child] + 1);
    }
    for (int cat = 1; cat <= p; ++cat) {
        int cat_tot;
        cin >> cat_tot;
        for (int i = 1; i <= cat_tot; ++i) {
            int toy;
            cin >> toy;
            toy_cat[toy] = cat;
        }
        cin >> cat_limit[cat];
    }
    cat_limit[0] = 128;

    for (int i = 1; i <= n; ++i) {
        child_order[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (child_sum[child_order[i]] > child_sum[child_order[j]]) {
                int tmp = child_order[i];
                child_order[i] = child_order[j];
                child_order[j] = tmp;
            }
        }
    }

    c = exp((150 - complexity) / n);
    search(1);

    cout << best << endl;

    return 0;
}
