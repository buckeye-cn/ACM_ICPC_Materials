#include <bits/stdc++.h>

using namespace std;

int N;
vector<string> I2N;
map<string, int> N2I;
queue<int> line;

constexpr int W = 0, B = 1, D = 0, O = 1;
int GAME[2][2];
int FIRST[2][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> N;

    I2N.resize(N);

    GAME[W][O] = 0;
    GAME[B][O] = 1;
    GAME[W][D] = 2;
    GAME[B][D] = 3;
    FIRST[W][0] = 0;
    FIRST[W][1] = 2;
    FIRST[B][0] = 1;
    FIRST[B][1] = 3;

    for (int i = 0; i < N; i++) {
        string n;
        cin >> n;
        I2N[i] = n;
        N2I[n] = i;
        if (i >= 4)
            line.push(i);
    }

    cin.get();

    int S[2] { 0, 0 };

    int sn = 0;
    vector<tuple<int, int>> st;

    for (;;) {
        auto c = cin.get();
        if (c == '\n')
            break;
        int TW, TL;
        if (c == 'W') {
            TW = W; TL = B;
        } else {
            TW = B; TL = W;
        }

        S[TW]++;
        S[TL] = 0;

        if (S[TW] > sn) {
            sn = S[TW];
            st.clear();
        }
        if (S[TW] == sn) {
            auto p1 = FIRST[TW][0], p2 = FIRST[TW][1];
            st.emplace_back(p1, p2);
        }

        swap(GAME[TW][D], GAME[TW][O]);
        line.push(GAME[TL][D]);
        GAME[TL][D] = GAME[TL][O];
        GAME[TL][O] = line.front();
        FIRST[TL][0] = GAME[TL][D];
        FIRST[TL][1] = GAME[TL][O];
        line.pop();
    }

    for (auto p : st) {
        cout << I2N[get<0>(p)] <<  ' ' << I2N[get<1>(p)] << endl;
    }
}
