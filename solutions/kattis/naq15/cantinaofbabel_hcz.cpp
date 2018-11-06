// https://open.kattis.com/problems/cantinaofbabel

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

template <long N>
struct Tarjan {
    vector<long> outs[N];

    void add(long from, long to) {
        outs[from].push_back(to);
    }

    long t_self[N];
    long t_low[N];

    vector<long> s;
    bool visiting[N];

    long now;
    long now_scc;

    void dfs(long (&scc)[N], long from) {
        t_self[from] = now;
        t_low[from] = now;
        now += 1;

        visiting[from] = true;
        s.push_back(from);

        for (long j = 0; j < outs[from].size(); ++j) {
            long to = outs[from][j];

            if (!t_self[to]) {
                dfs(scc, to);

                t_low[from] = min(t_low[from], t_low[to]);
            } else if (visiting[to]) {
                t_low[from] = min(t_low[from], t_self[to]);
            }
        }

        if (t_low[from] == t_self[from]) {
            while (true) {
                long to = s.back();
                s.pop_back();

                visiting[to] = false;
                scc[to] = now_scc;

                if (to == from) {
                    break;
                }
            }

            now_scc += 1;
        }
    }

    void solve(long (&scc)[N]) {
        memset(t_self, 0, sizeof(t_self));
        memset(visiting, 0, sizeof(visiting));

        now = 1;
        now_scc = 0;

        for (long i = 0; i < N; ++i) {
            if (!t_self[i]) {
                dfs(scc, i);
            }
        }
    }
};

Tarjan<120> tarjan;

int n;

int lang_tot;
string lang_name[120];
int lang_speaker[120];
unordered_map<string, int> lang;

long scc[120];
int scc_n[120];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        string name;
        string speak;
        cin >> name >> speak;

        if (lang.find(speak) == lang.end()) {
            lang_name[lang_tot] = speak;
            lang.insert({speak, lang_tot});
            ++lang_tot;
        }

        lang_speaker[lang[speak]] += 1;

        while (cin.peek() != '\n') {
            string know;
            cin >> know;

            if (lang.find(know) == lang.end()) {
                lang_name[lang_tot] = know;
                lang.insert({know, lang_tot});
                ++lang_tot;
            }

            tarjan.add(lang[know], lang[speak]);
        }
    }

    tarjan.solve(scc);

    for (int i = 0; i < lang_tot; ++i) {
        // cerr << scc[i] << ' ' << lang_name[i] << ' ' << lang_speaker[i] << endl;
        scc_n[scc[i]] += lang_speaker[i];
    }

    int best = 0;
    for (int i = 0; i < 120; ++i) {
        best = max(best, scc_n[i]);
    }

    cout << n - best << endl;

    return 0;
}
