// https://open.kattis.com/problems/isahasa

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

int n, m;
unordered_map<string, int> strpos;
string a[10000];
string r[10000];
string b[10000];
bool isa[500][500];
bool hasa[500][500];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> r[i] >> b[i];

        if (strpos.find(a[i]) == strpos.end()) {
            strpos[a[i]] = strpos.size() - 1;
        }
        if (strpos.find(b[i]) == strpos.end()) {
            strpos[b[i]] = strpos.size() - 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (r[i][0] == 'i') {
            isa[strpos[a[i]]][strpos[b[i]]] = true;
        } else {
            hasa[strpos[a[i]]][strpos[b[i]]] = true;
        }
    }

    int tot = strpos.size();

    for (int i = 0; i < tot; ++i) {
        isa[i][i] = true;
    }

    for (int i = 0; i < tot; ++i) {
        for (int j = 0; j < tot; ++j) {
            for (int k = 0; k < tot; ++k) {
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
