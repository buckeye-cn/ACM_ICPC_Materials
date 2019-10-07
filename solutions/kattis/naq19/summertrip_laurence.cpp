#include <bits/stdc++.h>

using namespace std;

uint32_t bi(char c) {
    return uint32_t(1) << (int)(c - 'a');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;
    cin >> s;

    auto it = unique(s.begin(), s.end());
    s.resize(distance(s.begin(), it));

    unordered_set<int> valid;
    vector<int>        invalid;
    vector<uint32_t>   fi;
    vector<uint32_t>   tt;
    fi.resize(s.size());
    tt.resize(s.size());

    long cc = 0;

    for (int j = 0; j < (int)s.size(); j++) {
        valid.insert(j);
        tt[j] |= bi(s[j]);
        fi[j] |= bi(s[j]);
    }

    for (int i = 1; i < (int)s.size(); i++) {
        for (int j : valid) {
            if (j >= ((int)s.size()) - i) {
                invalid.push_back(j);
                continue;
            }
            uint32_t b2 = bi(s.at(j + i));
            if ((tt[j] & b2) == 0) {
                cc++;
                tt[j] |= b2;
            } else if ((fi[j] & b2) != 0) {
                invalid.push_back(j);
            }
        }
        for (auto j : invalid) {
            valid.erase(j);
        }
        invalid.clear();
    }

    cout << cc << endl;
}
