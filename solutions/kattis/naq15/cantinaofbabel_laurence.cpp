#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string _LANG[2000] = {};
uint16_t n_l = 0;
inline uint16_t i_lang(string& lang) {
    for (uint16_t i = 0; i < n_l; i++)
        if (_LANG[i] == lang)
            return i;
    _LANG[n_l++] = lang;
    return n_l-1;
}

uint16_t N;

vector<uint16_t> p2l[100]  = {}; // langs understood by somebody
vector<uint16_t> l2p[2000] = {}; // people who understand a lang

bool conn[100][100] = {};

bool visited[100] = {};
vector<uint16_t> st = {};
void dfs(uint16_t i) {
    if (!visited[i]) {
        visited[i] = true;
        for (uint16_t j = 0; j < N; j++)
            if (conn[i][j])
                dfs(j);
        st.push_back(i);
    }
}

bool assigned[100] = {};
unordered_map<uint16_t, vector<uint16_t>> scc = {};
void assign(uint16_t i, uint16_t rt) {
    if (!assigned[i]) {
        assigned[i] = true;
        scc[rt].push_back(i);
        for (uint16_t j = 0; j < N; j++)
            if (!assigned[j] && conn[i][j])
                assign(j, rt);
    }
}

int main() {
    cin >> N;

    for (uint16_t i = 0; i < N; i++) {
        string name, lang;
        cin >> name >> lang;
        uint16_t i_l = i_lang(lang);
        p2l[i].push_back(i_l);
        l2p[i_l].push_back(i);
        while (cin.peek() != '\n') {
            cin >> lang;
            i_l = i_lang(lang);
            p2l[i].push_back(i_l);
            l2p[i_l].push_back(i);
        }
    }

    for (uint16_t i = 0; i < N; i++)
        for (uint16_t p : l2p[p2l[i][0]])
            conn[i][p] = true;

    for (uint16_t k = 0; k < N; k++)
        for (uint16_t i = 0; i < N; i++)
            for (uint16_t j = 0; j < N; j++)
                conn[i][j] |= conn[i][k] && conn[k][j];

    for (uint16_t i = 0; i < N; i++)
        dfs(i);

    for (uint16_t i : st)
        assign(i, i);

    uint16_t max_scc = 0;
    for (auto& _scc : scc)
        max_scc = max(max_scc, (uint16_t)_scc.second.size());
    cout << N-max_scc << endl;
}
