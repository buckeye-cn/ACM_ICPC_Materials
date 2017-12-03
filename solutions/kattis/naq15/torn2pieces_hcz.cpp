// https://open.kattis.com/problems/torn2pieces

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

unordered_map<string, unordered_map<string, bool>> conn;
unordered_map<string, string> path;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string src;
        cin >> src;
        path[src] = "";

        while (cin.get() != '\n') {
            string dest;
            cin >> dest;
            path[dest] = "";

            conn[src][dest] = true;
            conn[dest][src] = true;
        }
    }

    string first, last;
    cin >> first >> last;

    for (int iter = 0; iter < n; ++iter) {
        for (auto i: path) {
            if (!i.second.empty() || i.first == last) {
                for (auto j: conn[i.first]) {
                    if (path[j.first].empty()) {
                        path[j.first] = i.first;
                    }
                }
            }
        }
    }

    if (!path[first].empty()) {
        cout << first;

        while (first != last) {
            first = path[first];
            cout << ' ' << first;
        }

        cout << endl;
    } else {
        cout << "no route found" << endl;
    }

    return 0;
}
