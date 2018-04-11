#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

uint16_t n2i(string n) {
    static unordered_map<string, uint16_t> names;
    static uint16_t c = 0;
    auto names_it = names.find(n);
    if (names_it != names.end()) {
        return names_it->second;
    } else {
        names.emplace(n, c);
        return c++;
    }
}

struct {
    vector<uint16_t> ch;
    double sp;
} tree[1003];

struct {
    uint16_t init;
    uint16_t tc;
    double sp;
} table[1003][2]; // take?

void dd(uint16_t ni, uint8_t a) {
    auto& tb_node = table[ni];

    if (tb_node[a].init) {
        return;
    }

    auto const& node = tree[ni];

    if (node.ch.size() == 0) {
        tb_node[0].init = true;
        tb_node[1].init = true;
        return;
    }

    for (uint64_t cni : node.ch) {
        dd(cni, 1);
    }

    if (a == 0) { // not take
        for (uint64_t cni : node.ch) {
            tb_node[0].tc += table[cni][1].tc;
            tb_node[0].sp += table[cni][1].sp;
        }
        tb_node[0].init = true;
    } else {
        dd(ni, 0);
        tb_node[1].tc = tb_node[0].tc; // not take
        tb_node[1].sp = tb_node[0].sp; //
        for (uint64_t cni : node.ch) {
            dd(cni, 0);

            uint16_t new_tc = tb_node[0].tc - table[cni][1].tc + table[cni][0].tc + 1;
            if (new_tc > tb_node[1].tc) {
                tb_node[1].tc = new_tc;
                tb_node[1].sp = tb_node[0].sp - table[cni][1].sp + table[cni][0].sp + min(tree[cni].sp, node.sp);
            } else if (new_tc == tb_node[1].tc) {
                tb_node[1].sp = max(tb_node[1].sp,
                                tb_node[0].sp - table[cni][1].sp + table[cni][0].sp + min(tree[cni].sp, node.sp));
            }
        }
        tb_node[1].init = true;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint16_t N;
    cin >> N;

    uint16_t rt = -1;

    for (uint16_t i = 0; i < N; i++) {
        string na, svna; double sp;
        cin >> na >> sp >> svna;
        uint16_t ni = n2i(na);
        tree[ni].sp = sp;
        if (svna != "CEO") {
            uint16_t svni = n2i(svna);
            tree[svni].ch.push_back(ni);
        } else {
            rt = ni;
        }
    }

    dd(rt, 1);

    uint16_t tc = table[rt][1].tc;
    double sp = table[rt][1].sp;
    cout << tc << ' ' << sp / (double)tc << endl;
}
