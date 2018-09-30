#include <unordered_map>
#include <iostream>
#include "dijkstra.hpp"

using namespace std;

int count = 0;
unordered_map<uint32_t, int> mapping;
int point_index(uint32_t i, uint32_t j) {
    uint32_t k = (i << 16) | j;
    if (mapping.count(k) == 0)
        mapping.emplace(k, count++);
    return mapping.at(k);
}

inline void testcase() {
    count = 0;
    mapping.clear();

    int N;
    cin >> N;

    Dijkstra<long> dij(63);

    uint32_t i = 128, j = 128;

    auto prev = point_index(i, j);
    for (int pi = 0; pi < N; pi++) {
        char c;
        cin >> c;
        switch (c) {
            case 'N': i -= 1; break; case 'S': i += 1; break;
            case 'W': j -= 1; break; case 'E': j += 1; break;
        }
        auto curr = point_index(i, j);;
        dij.add_u(prev, curr, 1);
        prev = curr;
    }

    cout << dij.solve(0, prev) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        testcase();
    }
}
