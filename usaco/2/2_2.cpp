/*
ID: hu.13381
PROG: subset
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

int main() {
    ofstream fout ("subset.out");
    ifstream fin ("subset.in");

    int n;
    fin >> n;

    int sum = (1 + n) * n / 2;
    if (sum & 1) {
        fout << 0 << endl;
    } else {
        sum /= 2;

        static int s[10000] = {1};

        for (int i = 1; i < n; ++i) {
            for (int j = sum - i; j >= 0; --j) {
                s[j + i] += s[j];
            }
        }

        fout << s[sum] << endl;
    }

    return 0;
}
