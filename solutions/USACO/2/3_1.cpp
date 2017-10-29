/*
ID: hu.13381
PROG: prefix
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

bool ok[210000];

int main() {
    ofstream fout ("prefix.out");
    ifstream fin ("prefix.in");

    vector<string> words;
    while (true) {
        string s;
        fin >> s;
        if (s == ".") {
            break;
        } else {
            words.push_back(s);
        }
    }

    string target;
    while (!fin.eof()) {
        string s;
        fin >> s;
        target += s;
    }

    ok[0] = true;

    for (size_t i = 0; i < target.size(); ++i) {
        if (ok[i]) {
            for (string &word: words) {
                if (!ok[i + word.size()]) {
                    bool match = true;
                    for (size_t j = 0; j < word.size(); ++j) {
                        if (target[i + j] != word[j]) {
                            match = false;
                            break;
                        }
                    }
                    if (match) {
                        ok[i + word.size()] = true;
                    }
                }
            }
        }
    }

    for (int i = target.size(); i >= 0; --i) {
        if (ok[i]) {
            fout << i << endl;
            break;
        }
    }

    return 0;
}
