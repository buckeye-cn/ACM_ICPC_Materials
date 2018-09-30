// https://open.kattis.com/problems/quiteaproblem

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    char line[100];

    while (cin.getline(line, sizeof(line))) {
        int len = strlen(line);

        bool found = false;

        for (int i = 0; i < len - 6; ++i) {
            found |= (line[i] == 'P' || line[i] == 'p')
                && (line[i + 1] == 'R' || line[i + 1] == 'r')
                && (line[i + 2] == 'O' || line[i + 2] == 'o')
                && (line[i + 3] == 'B' || line[i + 3] == 'b')
                && (line[i + 4] == 'L' || line[i + 4] == 'l')
                && (line[i + 5] == 'E' || line[i + 5] == 'e')
                && (line[i + 6] == 'M' || line[i + 6] == 'm');
        }

        if (found) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    return 0;
}
