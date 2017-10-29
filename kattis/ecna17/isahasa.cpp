// https://open.kattis.com/problems/isahasa

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int n, m;
map<string, int> strpos;
string a[12000];
string r[12000];
string b[12000];
bool isa[600][600];
bool hasa[600][600];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> r[i] >> b[i];

        if (strpos.find(a[i]) == strpos.end()) {
            strpos[a[i]] = strpos.size();
        }
        if (strpos.find(b[i]) == strpos.end()) {
            strpos[b[i]] = strpos.size();
        }
    }

    for (int i = 0; i < n; ++i) {
        if (r[i][0] == 'i') {
            isa[strpos[a[i]]][strpos[b[i]]] = true;
        } else {
            hasa[strpos[a[i]]][strpos[b[i]]] = true;
        }
    }

    for (int i = 0; i < 600; ++i) {
        isa[i][i] = true;
    }

    for (int i = 0; i < 600; ++i) {
        for (int j = 0; j < 600; ++j) {
            for (int k = 0; k < 600; ++k) {
                if (isa[j][i] && isa[i][k]) isa[j][k] = true;
                if (isa[j][i] && hasa[i][k]) hasa[j][k] = true;
                if (hasa[j][i] && isa[i][k]) hasa[j][k] = true;
                if (hasa[j][i] && hasa[i][k]) hasa[j][k] = true;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        string aa, rr, bb;
        cin >> aa >> rr >> bb;
        if (rr[0] == 'i') {
            cout << "Query " << (i + 1) << ": " << (isa[strpos[aa]][strpos[bb]] ? "true" : "false") << endl;
        } else {
            cout << "Query " << (i + 1) << ": " << (hasa[strpos[aa]][strpos[bb]] ? "true" : "false") << endl;
        }
    }

    return 0;
}
