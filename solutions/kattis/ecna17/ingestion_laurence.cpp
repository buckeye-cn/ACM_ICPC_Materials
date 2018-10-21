#include <bits/stdc++.h>

using namespace std;

int N;
int course[103];
int upper[103];
int table[103][103][4];

int rdp(int ci, int ui, int ce);
int crdp(int ci, int ui, int se) {
    se &= 0b11;
    ui = se ? ui : 0;
    auto& r = table[ci][ui][se];
    if (r < 0)
        r = rdp(ci, ui, se);
    return r;
}
int rdp(int ci, int ui, int se) {
    int e = min(course[ci], upper[ui]);
    if (ci >= N-1)
        return e;
    else
        return max(crdp(ci + 1, ui + 1, (se << 1) | 1) + e, crdp(ci + 1, ui - 1, se << 1));
}

int idp(int ci, int ui, int se) {
    for (int ci = N-1; ci >= 0; ci--)
        for (int ui = N-1; ui >= 0; ui--)
            for (int se = 0; se < 4; se++)
                if (ci == N-1)
                    table[ci][ui][se] = min(course[ci], upper[ui]);
                else
                    table[ci][ui][se] = max(table[ci+1][ui+1][((se << 1) & 0b11) | 1] + min(course[ci], upper[ui]), table[ci+1][((se << 1) & 0b11) ? ui-1 : 0][(se << 1) & 0b11]);
    return table[ci][ui][se];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    memset(table, -1, sizeof(table));

    int M;

    cin >> N >> M;

    for (int i = 0; i < N; i++)
        cin >> course[i];

    upper[0] = M;
    for (int i = 1; i < N; i++)
        upper[i] = upper[i-1]*2/3;

    //cout << crdp(0, 0, 0) << endl;
    cout << idp(0, 0, 0) << endl;

#ifdef DEBUG
    for (int ci = 0; ci < N; ci++) {
        cerr << " " << ci << "(" << course[ci] << ") ";
        for (int ui = 0; ui < N; ui++) {
            for (int se = 0; se < 4; se++) {
                cerr << setw(4) << table[ci][ui][se] << ',';
            }
            cerr << '\t';
        }
        cerr << '\n';
    }
#endif
}
