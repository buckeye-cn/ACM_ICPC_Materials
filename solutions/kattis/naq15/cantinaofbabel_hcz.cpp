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

    long id_self[N];
    long id_low[N];
    long route[N];

    void dfs(long (&scc)[N], long from, long &last, long &now, long &now_scc) {
        id_self[from] = now;
        id_low[from] = now;
        now += 1;

        route[from] = last;
        last = from;

        for (long j = 0; j < outs[from].size(); ++j) {
            long to = outs[from][j];

            if (!id_self[to]) {
                dfs(scc, to, last, now, now_scc);

                id_low[from] = min(id_low[from], id_low[to]);
            } else if (!scc[to]) {
                id_low[from] = min(id_low[from], id_self[to]);
            }
        }

        if (id_low[from] == id_self[from]) {
            while (last != from) {
                scc[last] = now_scc;
                last = route[last];
            }

            scc[last] = now_scc;
            last = route[last];
            now_scc += 1;
        }
    }

    void solve(long (&scc)[N]) {
        memset(id_self, 0, sizeof(id_self));

        long last = 0;
        long now = 1;
        long now_scc = 1;

        for (long i = 0; i < N; ++i) {
            if (!id_self[i]) {
                dfs(scc, i, last, now, now_scc);
            }
        }

        for (long i = 0; i < N; ++i) {
            scc[i] -= 1;
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
