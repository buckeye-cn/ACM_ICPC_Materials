#include <bits/stdc++.h>

using namespace std;

vector<int64_t> ba, bb, bt;

bool at_back(vector<int64_t> const& v, int64_t x) {
    return !v.empty() && v.back() == x;
}

int64_t dp(int64_t depth) {
    if (depth < 1)
        return 0;

    int64_t res = 0;

    if (at_back(ba, depth)) {
        res += 1l << (depth - 1);
        ba.pop_back();
        swap(bt, bb);
    } else if (at_back(bb, depth)) {
        bb.pop_back();
        swap(bt, ba);
    } else {
        return -999;
    }

    int64_t subres = dp(depth-1);

    return subres>=0 ? res+subres : subres;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int64_t ND = 0;

    auto read = [&](vector<int64_t>& b) {
        int64_t N;
        cin >> N;
        int64_t x0 = 99;
        for (int64_t j = 0; j < N; j++) {
            int64_t x;
            cin >> x;
            if (x < x0) {
                b.insert(b.begin(), x);
                x0 = x;
                ND = max(ND, x);
            } else {
                cout << "No\n";
                exit(0);
            }
        }
    };

    read(ba);
    read(bt);
    read(bb);

    int64_t s = dp(ND);
    if (s >= 0) {
        cout << s << endl;
    } else {
        cout << "No\n";
    }
}
