// https://open.kattis.com/problems/wordequations

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;

        unordered_map<string, pair<string, string>> rules;
        unordered_map<string, string> words;
        unordered_map<string, vector<int>> transform;

        for (int j = 0; j < k; ++j) {
            string s1, s2, s3;
            cin >> s1 >> s2 >> s2;

            if (s2[0] <= 'Z') {
                cin >> s3 >> s3;
                rules.insert({s1, {s2, s3}});
            } else {
                words.insert({s1, s2});
            }

            transform.insert({s1, {}});
        }

        string sw, sf;
        cin >> sw >> sf;

        for (pair<string, string> p: words) {
            vector<int> &v = transform[p.first];

            for (int i = 0; i < sf.size(); ++i) {
                int j = i;
                int k = 0;

                for (; j < sf.size(); ++j, ++k) {
                    for (; k < p.second.size() && sf[j] != p.second[k]; ++k);

                    if (k == p.second.size()) break;
                }

                v.push_back(j);
            }

            v.push_back(sf.size());
        }

        while (true) {
            bool changed = false;

            for (pair<string, pair<string, string>> p: rules) {
                vector<int> &v = transform[p.first];

                if (!v.empty()) continue;

                vector<int> &v1 = transform[p.second.first];
                vector<int> &v2 = transform[p.second.second];

                if (!v1.empty() && !v2.empty()) {
                    for (int i = 0; i < sf.size(); ++i) {
                        v.push_back(v2[v1[i]]);
                    }

                    v.push_back(sf.size());

                    changed = true;
                }
            }

            if (!changed) break;
        }

        if (transform[sw][0] == sf.size()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
