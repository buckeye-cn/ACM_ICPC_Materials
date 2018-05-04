#include <iostream>
#include <vector>

using namespace std;

inline void add_mod(uint64_t& dst, uint64_t o) noexcept {
    constexpr uint64_t MM = 1e9 + 7;
    dst += o;
    dst %= MM;
}

struct Node {
    bool is_red;
    vector<Node*> children;
    vector<uint64_t> ss; // # of red nodes -> # of ways (non-empty)

    inline uint16_t nr() const { return ss.size() - 1; }
    inline void set_nr(uint16_t n) { ss.resize(n + 1); }
};

void cpp(Node* const root) {
    if (root->children.empty()) {
        root->set_nr(root->is_red);
        root->ss[root->is_red] = 1;
    } else {
        uint16_t nr = 0;
        for (Node const* child : root->children)
            nr += child->nr();
        if (nr < root->is_red)
            nr = 1;
        root->set_nr(nr);

        vector<uint64_t> _ss;
        uint16_t _nr = 0;
        for (Node const* child : root->children) {
            _ss = root->ss;
            for (uint16_t cr = 0; cr <= child->nr(); cr++) {
                add_mod(root->ss[cr], child->ss[cr]);   // only this child
                for (uint16_t r = 0; r <= _nr; r++)     // .. and with other children
                    add_mod(root->ss[cr + r], child->ss[cr] * _ss[r]);
            }
            _nr += child->nr();
        }

        // take root
        if (root->is_red)
            add_mod(root->ss[1], 1);
        else
            add_mod(root->ss[0], 1);
    }
}

void dfs(Node* const rt) { // post order dfs
    struct TODO {
        Node* const node;
        uint32_t const nch;
        uint32_t i;

        TODO(Node* _node) : node(_node), nch(_node->children.size()), i(0) {}
    };
    vector<TODO> todo { { rt } };
    while (!todo.empty()) {
        TODO& la = todo.back();
        if (la.i < la.nch) {
            todo.push_back({ la.node->children[la.i++] });
        } else {
            cpp(la.node);
            todo.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint32_t N, M;
    cin >> N >> M;

    Node* const nodes = new Node[N]() - 1; // we start from 1..

    for (uint32_t i = 2; i <= N; i++) {
        uint32_t p;
        cin >> p;
        nodes[p].children.push_back(&nodes[i]);
    }
    for (uint32_t i = 0; i < M; i++) {
        uint32_t ni;
        cin >> ni;
        nodes[ni].is_red = true;
    }

    Node* const rt = &nodes[1];
    dfs(rt);
    rt->ss[0]++;
    for (uint16_t k = 0; k <= M; k++) {
        if (k <= rt->nr())
            cout << rt->ss[k] << '\n';
        else
            cout << 0 << '\n';
    }
}
