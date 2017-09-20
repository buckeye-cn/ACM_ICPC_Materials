/*
ID: hu.13381
PROG: namenum
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
    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");

    ifstream dict ("dict.txt");

    string input;
    fin >> input;
    bool p = false;
    while (!dict.eof()) {
        string x;
        dict >> x;
        if (x.size() != input.size()) continue;

        int i = 0;
        for (; i < x.size(); ++i) {
            switch (input[i]) {
                case '2':
                    if (x[i] < 'A' || x[i] > 'C') i = 1000;
                    break;
                case '3':
                    if (x[i] < 'D' || x[i] > 'F') i = 1000;
                    break;
                case '4':
                    if (x[i] < 'G' || x[i] > 'I') i = 1000;
                    break;
                case '5':
                    if (x[i] < 'J' || x[i] > 'L') i = 1000;
                    break;
                case '6':
                    if (x[i] < 'M' || x[i] > 'O') i = 1000;
                    break;
                case '7':
                    if (x[i] < 'P' || x[i] > 'S' || x[i] == 'Q') i = 1000;
                    break;
                case '8':
                    if (x[i] < 'T' || x[i] > 'V') i = 1000;
                    break;
                case '9':
                    if (x[i] < 'W' || x[i] > 'Y') i = 1000;
                    break;
            }
        }
        if (i == x.size()) {
            fout << x << endl;
            p = true;
        }
    }
    if (!p) {
        fout << "NONE" << endl;
    }

    return 0;
}
