// https://open.kattis.com/problems/exam

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int k;
    cin >> k;

    string s1, s2;
    cin >> s1 >> s2;

    int same = 0;
    for (int i = 0; i < s1.size(); ++i) {
        same += s1[i] == s2[i];
    }

    cout << min(k, same) + s1.size() - max(k, same) << endl;

    return 0;
}
