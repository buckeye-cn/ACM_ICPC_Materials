// https://open.kattis.com/problems/lemonadetrade

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    unordered_map<string, double> max_v;

    max_v.insert({"pink", 0});

    for (int i = 0; i < n; ++i) {
        string o, w;
        double r;
        cin >> o >> w >> r;

        if (max_v.find(w) == max_v.end()) {
            // nothing
        } else if (max_v.find(o) == max_v.end()) {
            max_v.insert({o, max_v[w] + log(r)});
        } else {
            max_v[o] = max(max_v[o], max_v[w] + log(r));
        }
    }

    if (max_v.find("blue") == max_v.end()) {
        cout << 0. << endl;
    } else if (max_v["blue"] > log(10)) {
        cout << 10. << endl;
    } else {
        cout << exp(max_v["blue"]) << endl;
    }

    return 0;
}
