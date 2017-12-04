/*
ID: hu.13381
PROG: friday
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool leap(int yr) {
    return ((yr % 4 == 0) && (yr % 100 != 0)) || (yr % 400 == 0);
}

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");

    int day_offset1[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day_offset2[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // {
    //     int s = 0;
    //     for (auto &i: day_offset1) {
    //         s += i;
    //         i = s;
    //     }
    //     s = 0;
    //     for (auto &i: day_offset2) {
    //         s += i;
    //         i = s;
    //     }
    // }

    int tot;
    fin >> tot;
    int result[7] = {};

    int xx = 0;
    for (int i = 0; i < tot; ++i) {
        for (int j = 0; j < 12; ++j) {
            ++result[xx];
            xx = (xx + (leap(i + 1900) ? day_offset2: day_offset1)[j]) % 7;
        }
    }

    for (int i = 0; i < 6; ++i) {
        fout << result[i] << ' ';
    }
    fout << result[6] << '\n';

    return 0;
}
