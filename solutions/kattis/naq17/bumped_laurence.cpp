#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

constexpr uint32_t LAYER_M = 1l << 24;

unordered_multimap<uint32_t, uint32_t> roads = {};
unordered_multimap<uint32_t, uint32_t> flights = {};

unordered_map<uint32_t, uint32_t> cost = {};

set<uint64_t> todo = {};
unordered_set<uint32_t> visited = {};

inline void new_todo(uint64_t city, uint64_t cost_n) {
    todo.insert((cost_n << 32) + city);
}

inline void update_todo(uint64_t city, uint64_t cost_o, uint64_t cost_n) {
    todo.erase((cost_o << 32) + city);
    new_todo(city, cost_n);
};

inline void pop_todo(uint32_t& c, uint32_t& c_cost) {
    auto td_p = todo.begin();
    uint64_t td = *td_p;
    todo.erase(td_p);
    c_cost = td >> 32;
    c      = td & 0xffffffff;
    visited.insert(c);
}

inline void update(uint32_t city, uint32_t cost_alt) {
    if (visited.count(city) == 0) {
        if (cost.count(city) > 0) {
            uint32_t cost_o = cost[city];
            uint32_t cost_n = min(cost_o, cost_alt);
            if (cost_o != cost_n) {
                cost[city] = cost_n;
                update_todo(city, cost_o, cost_n);
            }
        } else {
            cost[city] = cost_alt;
            new_todo(city, cost_alt);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    unsigned N, M, F, S, T;
    cin >> N >> M >> F >> S >> T;

    roads.reserve(M);
    flights.reserve(F);
    cost.reserve(N);
    visited.reserve(N);

    for (unsigned i = 0; i < M; i++) {
        unsigned c1, c2, c;
        cin >> c1 >> c2 >> c;
        roads.insert(make_pair(c1, (c2 << 16) + c));
        roads.insert(make_pair(c2, (c1 << 16) + c));
    }

    for (unsigned i = 0; i < F; i++) {
        unsigned c1, c2;
        cin >> c1 >> c2;
        flights.insert(make_pair(c1, c2));
    }

    update(S, 0);

    while (todo.size() > 0) {
        uint32_t c_l, c_cost;
        pop_todo(c_l, c_cost);

        uint32_t c = c_l & ~LAYER_M;
        uint32_t l = c_l & LAYER_M;

        if (c == T) {
            cout << c_cost << "\n";
            return 0;
        }

        auto road_range = roads.equal_range(c);
        for (auto it = road_range.first; it != road_range.second; it++) {
            update(it->second >> 16 | l, c_cost + (it->second & 0xffff));
        }

        if (l == 0) {
            auto flight_range = flights.equal_range(c);
            for (auto it = flight_range.first; it != flight_range.second; it++) {
                update(it->second | LAYER_M, c_cost);
            }
        }
    }

    return 1;
}
