// https://open.kattis.com/problems/raggedright

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    vector<int> lens;
    int maxlen = 0;

    char line[100];

    while (cin.getline(line, sizeof(line))) {
        int len = strlen(line);

        lens.push_back(len);
        maxlen = max(maxlen, len);
    }

    uint64_t result = 0;

    for (int i = 0; i < lens.size() - 1; ++i) {
        result += (maxlen - lens[i]) * (maxlen - lens[i]);
    }

    cout << result << endl;

    return 0;
}
