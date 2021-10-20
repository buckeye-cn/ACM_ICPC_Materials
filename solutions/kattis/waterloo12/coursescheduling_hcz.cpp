// https://open.kattis.com/problems/coursescheduling

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    set<pair<string, string>> s;

    for (int i = 0; i < n; ++i) {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;

        s.insert({s3, s1 + ' ' + s2});
    }

    string last;
    int count = 0;

    for (pair<string, string> p: s) {
        if (p.first != last) {
            if (count) {
                cout << last << ' ' << count << endl;
            }

            last = p.first;
            count = 1;
        } else {
            count += 1;
        }
    }

    if (count) {
        cout << last << ' ' << count << endl;
    }

    return 0;
}
