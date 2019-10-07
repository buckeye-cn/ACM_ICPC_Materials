#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N;
    cin >> N;

    vector<int>        nums;
    unordered_set<int> numss;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        nums.push_back(x);
        numss.insert(x);
    }
    bool missing = false;
    for (int i = 1; i <= nums.back(); i++) {
        if (!numss.count(i)) {
            missing = true;
            cout << i << endl;
        }
    }
    if (!missing) {
        cout << "good job" << endl;
    }
}
