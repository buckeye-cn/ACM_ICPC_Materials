#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N;
    cin >> N;

    vector<bool> var;
    var.resize(N);
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        if (s[0] == 'T') {
            var[i] = true;
        } else {
            var[i] = false;
        }
    }

    cin.get();

    vector<bool> st;

    while (true) {
        char c = cin.get();
        if (('A' <= c && c <= 'Z')) {
            st.push_back(var[c - 'A']);
        } else if (c == '-') {
            st.back() = !st.back();
        } else if (c == '+') {
            bool b1 = st.back();
            st.pop_back();
            bool b2 = st.back();
            st.pop_back();
            st.push_back(b1 || b2);
        } else if (c == '*') {
            bool b1 = st.back();
            st.pop_back();
            bool b2 = st.back();
            st.pop_back();
            st.push_back(b1 && b2);
        } else {
            break;
        }
        cin.get();
    }

    cout << (st.back() ? 'T' : 'F') << endl;
}
