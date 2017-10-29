/*
ID: hu.13381
PROG: preface
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
    ofstream fout ("preface.out");
    ifstream fin ("preface.in");

    const int nums[13] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    const string is[13] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

    int n;
    fin >> n;

    map<char, int> chars = {
        {'I', 0},
        {'V', 0},
        {'X', 0},
        {'L', 0},
        {'C', 0},
        {'D', 0},
        {'M', 0}
    };
    for (int i = 1; i <= n; ++i) {
        int val = i;
        for (int j = 12; j >= 0; --j) {
            while (val >= nums[j]) {
                val -= nums[j];
                for (char k: is[j]) {
                    chars[k] += 1;
                }
            }
        }
    }
    #define outx(c) if (chars[c]) fout << c << ' ' << chars[c] << endl;
    outx('I')
    outx('V')
    outx('X')
    outx('L')
    outx('C')
    outx('D')
    outx('M')

    return 0;
}
