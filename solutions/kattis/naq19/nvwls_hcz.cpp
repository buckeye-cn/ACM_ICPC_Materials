// https://open.kattis.com/problems/nvwls

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

string s[100000];
int vowel[100000];
int consonant[100000];

unordered_map<int, unordered_map<int, int>> dicts;

int key_total;
int keys[1000];
int hash_roll[1000];
int hash_tail[1000];
int one_hash[1000];
int one_pos[1000];

int best[300001];
int best_pos[300001];

int result_total;
int results[300000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> s[i];

        int hash = 0;

        for (char c: s[i]) {
            if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                vowel[i] += 1;
            } else {
                consonant[i] += 1;

                hash *= 1000000007;
                hash += c;
            }
        }

        unordered_map<int, int> &dict = dicts[consonant[i]];

        if (dict.find(hash) == dict.end() || vowel[dict[hash]] < vowel[i]) {
            dict[hash] = i;
        }
    }

    string ss;
    cin >> ss;

    for (auto i: dicts) {
        keys[key_total] = i.first;
        hash_tail[key_total] = 1;

        if (i.second.size() == 1) {
            one_hash[key_total] = i.second.begin()->first;
            one_pos[key_total] = i.second.begin()->second;
        }

        key_total += 1;
    }

    for (int i = 0; i < ss.size(); ++i) {
        best[i + 1] = -1;

        for (int j = 0; j < key_total; ++j) {
            hash_roll[j] *= 1000000007;
            hash_roll[j] += ss[i];

            if (i < keys[j]) {
                hash_tail[j] *= 1000000007;
            } else {
                hash_roll[j] -= hash_tail[j] * ss[i - keys[j]];
            }

            if (i + 1 >= keys[j] && best[i + 1 - keys[j]] >= 0) {
                int pos = -1;

                if (hash_roll[j] == one_hash[j]) {
                    pos = one_pos[j];
                } else {
                    unordered_map<int, int> &dict = dicts[keys[j]];

                    if (dict.find(hash_roll[j]) != dict.end()) {
                        pos = dict[hash_roll[j]];
                    }
                }

                if (pos != -1 && best[i + 1] < best[i + 1 - keys[j]] + vowel[pos]) {
                    best[i + 1] = best[i + 1 - keys[j]] + vowel[pos];
                    best_pos[i + 1] = pos;
                }
            }
        }
    }

    for (int i = ss.size(); i; i -= consonant[best_pos[i]]) {
        results[result_total++] = best_pos[i];
    }

    for (int i = result_total - 1; i >= 0; --i) {
        cout << s[results[i]];

        if (i) {
            cout << ' ';
        } else {
            cout << endl;
        }
    }

    return 0;
}
