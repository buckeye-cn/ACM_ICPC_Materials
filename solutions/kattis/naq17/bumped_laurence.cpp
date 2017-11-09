#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

constexpr uint32_t inf_c = ~0;
constexpr uint32_t layer_m = 1l << 24;

unordered_multimap<uint32_t, uint32_t> roads = {};
unordered_multimap<uint32_t, uint32_t> flights = {};

unordered_map<uint32_t, uint32_t> cost = {};

set<uint64_t> todo = {};
unordered_set<uint32_t> visited = {};

inline void new_todo(uint64_t city, uint64_t cost_n) {
    todo.insert((cost_n << 32) + city);
}

inline void update_todo(uint64_t city, uint64_t cost_o, uint64_t cost_n) {
    auto td_o = todo.find((cost_o << 32) + city);
    if (td_o != todo.end()) {
        todo.erase(td_o);
        todo.insert((cost_n << 32) + city);
    } else if (visited.count(city) == 0) {
        new_todo(city, cost_n);
    }
};

inline void pop_todo(uint32_t& city, uint32_t& cost_n) {
    auto td_p = todo.begin();
    uint64_t td = *td_p;
    todo.erase(td_p);
    cost_n = td >> 32;
    city = td & 0xffffffff;
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

    new_todo(S, 0);

    cost.insert(make_pair(S, 0));

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

    while (todo.size() > 0) {
        uint32_t c_l, c_cost;
        pop_todo(c_l, c_cost);
        visited.insert(c_l);
        uint32_t c = c_l & ~layer_m;
        uint32_t l = c_l & layer_m;

        if (c == T) {
            cout << c_cost << "\n";
            return 0;
        }

        auto road_range = roads.equal_range(c);
        for (auto it = road_range.first; it != road_range.second; it++) {
            uint32_t adj = it->second >> 16 | l;
            uint32_t road_c = it->second & 0xffff;
            uint32_t adj_c_o = (cost.count(adj) > 0) ? cost[adj] : inf_c;
            uint32_t adj_c_n = min(adj_c_o, c_cost + road_c);
            cost[adj] = adj_c_n;
            update_todo(adj, adj_c_o, adj_c_n);
        }

        if (l == 0) {
            auto flight_range = flights.equal_range(c);
            for (auto it = flight_range.first; it != flight_range.second; it++) {
                uint32_t c1 = it->second | layer_m;
                uint32_t c1_c_o = (cost.count(c1) > 0) ? cost[c1] : inf_c;
                uint32_t c1_c_n = min(c1_c_o, c_cost);
                cost[c1] = c1_c_n;
                update_todo(c1, c1_c_o, c1_c_n);
            }
        }
    }

    return 1;
}
