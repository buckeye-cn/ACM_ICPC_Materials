// https://open.kattis.com/problems/allinthefamily

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

int pp[1001];
int dd[1001];
int cc[1001][1001];
int depth[1001];

void dfs(int k, int level) {
    depth[k] = level;

    for (int i = 0; i < dd[k]; ++i) {
        dfs(cc[k][i], level + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t, p;
    cin >> t >> p;

    unordered_map<string, int> names;

    for (int i = 0; i < t; ++i) {
        string s1;
        cin >> s1;

        int k1 = names.insert({s1, names.size() + 1}).first->second;

        cin >> dd[k1];

        for (int j = 0; j < dd[k1]; ++j) {
            string s2;
            cin >> s2;

            int k2 = names.insert({s2, names.size() + 1}).first->second;

            pp[k2] = k1;
            cc[k1][j] = k2;
        }
    }

    for (int k = 1; k <= names.size(); ++k) {
        if (!pp[k]) {
            dfs(k, 0);
        }
    }

    for (int i = 0; i < p; ++i) {
        string s1, s2;
        cin >> s1 >> s2;

        int k1 = names[s1];
        int k2 = names[s2];

        int d = 0;
        int e = 0;

        while (depth[k1] > depth[k2]) {
            k1 = pp[k1];
            d += 1;
        }

        while (depth[k1] < depth[k2]) {
            k2 = pp[k2];
            e += 1;
        }

        while (k1 != k2) {
            k1 = pp[k1];
            k2 = pp[k2];
            d += 1;
            e += 1;
        }

        if (d == 0 && e == 1) {
            cout << s2 << " is the child of " << s1 << endl;
        } else if (d == 0) {
            cout << s2 << " is the";

            for (int j = 0; j < e - 2; ++j) {
                cout << " great";
            }

            cout << " grandchild of " << s1 << endl;
        } else if (d == 1 && e == 0) {
            cout << s1 << " is the child of " << s2 << endl;
        } else if (e == 0) {
            cout << s1 << " is the";

            for (int j = 0; j < d - 2; ++j) {
                cout << " great";
            }

            cout << " grandchild of " << s2 << endl;
        } else if (d == 1 && e == 1) {
            cout << s1 << " and " << s2 << " are siblings" << endl;
        } else {
            int cousin = min(d, e) - 1;

            cout << s1 << " and " << s2 << " are " << cousin;

            if (cousin % 10 == 1 && cousin != 11) {
                cout << "st";
            } else if (cousin % 10 == 2 && cousin != 12) {
                cout << "nd";
            } else if (cousin % 10 == 3 && cousin != 13) {
                cout << "rd";
            } else {
                cout << "th";
            }

            cout << " cousins";

            int removed = abs(d - e);

            if (removed == 1) {
                cout << ", 1 time removed";
            } else if (removed > 1) {
                cout << ", " << removed << " times removed";
            }

            cout << endl;
        }
    }

    return 0;
}
