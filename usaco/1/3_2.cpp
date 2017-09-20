/*
ID: hu.13381
PROG: barn1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");

    int m, s, c;
    set<int> need;

    fin >> m >> s >> c;
    for (int i = 0; i < c; ++i) {
        int x;
        fin >> x;
        need.insert(x);
    }

    map<int, int> subs;
    int sum = 1 - m;
    int last = -1;
    for (int i: need) {
        if (last == -1) {
            last = i;
        } else {
            if (subs.find(i - last) != subs.end()) {
                subs[i - last] += 1;
                sum += 1;
            } else {
                subs[i - last] = 1;
                sum += 1;
            }
            last = i;
        }
    }

    int result = m < c ? m : c;
    for (auto i: subs) {
        if (sum > i.second) {
            result += i.first * i.second;
            sum -= i.second;
        } else if (sum > 0) {
            result += i.first * sum;
            sum = 0;
            break;
        }
    }

    fout << result << endl;

    return 0;
}
