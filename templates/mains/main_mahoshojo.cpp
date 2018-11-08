// code template for competitions
// g++ --std=c++11 -Wall -g -O0 ???.cpp && time ./a.out < in

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>

#include <string>
#include <tuple>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>

#include <functional>
#include <algorithm>
#include <random>
#include <iostream>

#define sqr(x) ((x) * (x))
#define shl(x) (__int128(1) << (x))

const double PI = acos(-1);
const double EE = exp(1);

using namespace std;

long n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (long i = 0; i < n; ++i) {
        long x, y;
        cin >> x >> y;
    }

    cout << "Hello" << endl;
    cout << PI << ' ' << EE << endl;

    return 0;
}
