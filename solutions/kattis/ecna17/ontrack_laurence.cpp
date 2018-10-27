#include <bits/stdc++.h>

using namespace std;

struct Node {
    int conn[10003];
    uint32_t weight;
};

int N_EDGE;
int N_NODE;
Node NODES[10003];
bool CHECKED[10003];
uint32_t min_weight = -1;
uint32_t min_weight_node = -1;

int dfs(int i, int prev = -1) {
    CHECKED[i] = 1;
    int cc = 1;
    uint32_t weight = 0;
    for (int j=0; j<N_NODE; j++) {
        if (NODES[i].conn[j] < 0 && !CHECKED[j]) {
            int x = dfs(j , i);
            NODES[i].conn[j] = x;
            cc += x;
            weight += x * (x-1);
        }
    }
    if (prev >= 0) {
        int x = N_NODE-cc;
        NODES[i].conn[prev] = x;
        weight += x * (x-1);
    }
    weight >>= 1;
    NODES[i].weight = weight;
    if (weight < min_weight) {
        min_weight = weight;
        min_weight_node = i;
    }

    return cc;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> N_EDGE;
    N_NODE = N_EDGE+1;

    for (int i = 0; i < N_EDGE; i++) {
        int a,b;
        cin>>a>>b;
        NODES[a].conn[b]=-1;
        NODES[b].conn[a]=-1;
    }

    dfs(0);

    uint32_t n1 = N_EDGE * (N_EDGE-1) / 2 - min_weight;

    int x1 = -1, x2 = -1;
    for (int j=0; j<N_NODE; j++) {
        int cc = NODES[min_weight_node].conn[j];
        if (cc > x1) {
            x2 = x1;
            x1 = cc;
        } else if (cc > x2) {
            x2 = cc;
        }
    }

    cout << n1 << ' ' << n1 - x1 * x2 << endl;
}
