#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

string s;
int LEN;
bool EQ[100][100] = {};

int main() {
    cin >> s;

    LEN = s.length();

    for (int i = 0; i < LEN; i++)
        for (int j = 0; j < LEN; j++)
            EQ[i][j] = s[i] == s[j];

    int min_len = LEN;
    for (int len = 2; len < LEN/2; len++) {
        for (int i = 1; i < LEN-len+1; i++) {
            for (int j = 0; j < LEN-len+1; j++) {
                EQ[i][j] &= s[i+len-1] == s[j+len-1];
            }
        }

        map<string, int> c = {};
        for (int i = 1; i < LEN-len+1; i++) {
            string subs = s.substr(i, len);
            if (c.count(subs)) {
                continue;
            }
            c[subs] = 0;
            int j = 0;
            while (j < LEN-len+1) {
                if (EQ[i][j]) {
                    c[subs] += 1;
                    j += len;
                } else {
                    j += 1;
                }
            }
        }

        if (c.size() == 0) {
            break;
        }

        int max_m = 0;
        for (auto p : c) {
            max_m = max(max_m, p.second);
        }

        int len_res = LEN - max_m * (len-1) + len;
        min_len = min(min_len, len_res);
    }

    cout << min_len << endl;
}
