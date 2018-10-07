// https://open.kattis.com/problems/peggamefortwo

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int dfs(string &s);

int check(string &s, int i, int j, int k) {
    if (!s[i]) return -99999;
    if (!s[j]) return -99999;
    if (s[k]) return -99999;

    int a = s[i];
    int b = s[j];

    s[i] = 0;
    s[j] = 0;
    s[k] = a;

    int result = a * b - dfs(s);

    s[i] = a;
    s[j] = b;
    s[k] = 0;

    return result;
}

int dfs(string &s) {
    int best = -99999;

    best = max(best, check(s, 0, 1, 3));
    best = max(best, check(s, 1, 3, 6));
    best = max(best, check(s, 3, 6, 10));
    best = max(best, check(s, 2, 4, 7));
    best = max(best, check(s, 4, 7, 11));
    best = max(best, check(s, 5, 8, 12));

    best = max(best, check(s, 10, 11, 12));
    best = max(best, check(s, 11, 12, 13));
    best = max(best, check(s, 12, 13, 14));
    best = max(best, check(s, 6, 7, 8));
    best = max(best, check(s, 7, 8, 9));
    best = max(best, check(s, 3, 4, 5));

    best = max(best, check(s, 14, 9, 5));
    best = max(best, check(s, 9, 5, 2));
    best = max(best, check(s, 5, 2, 0));
    best = max(best, check(s, 13, 8, 4));
    best = max(best, check(s, 8, 4, 1));
    best = max(best, check(s, 12, 7, 3));

    best = max(best, check(s, 3, 1, 0));
    best = max(best, check(s, 6, 3, 1));
    best = max(best, check(s, 10, 6, 3));
    best = max(best, check(s, 7, 4, 2));
    best = max(best, check(s, 11, 7, 4));
    best = max(best, check(s, 12, 8, 5));

    best = max(best, check(s, 12, 11, 10));
    best = max(best, check(s, 13, 12, 11));
    best = max(best, check(s, 14, 13, 12));
    best = max(best, check(s, 8, 7, 6));
    best = max(best, check(s, 9, 8, 7));
    best = max(best, check(s, 5, 4, 3));

    best = max(best, check(s, 5, 9, 14));
    best = max(best, check(s, 2, 5, 9));
    best = max(best, check(s, 0, 2, 5));
    best = max(best, check(s, 4, 8, 13));
    best = max(best, check(s, 1, 4, 8));
    best = max(best, check(s, 3, 7, 12));

    if (best == -99999) return 0;

    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;

    for (int i = 0; i < 15; ++i) {
        int value;
        cin >> value;

        s.push_back(char(value));
    }

    cout << dfs(s) << endl;

    return 0;
}
