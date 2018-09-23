#include <deque>
#include <iostream>

using namespace std;

int main() {
    for (int n = 1; n <= 13; n++) {
        deque<int> dq;
        for (int i = n; i >= 1; i--) {
            dq.push_front(i);
            for (int _i = 0; _i < i; _i++) {
                dq.push_front(dq.back());
                dq.pop_back();
            }
        }
        cout << "\"";
        for (auto c : dq) {
            cout << c << ' ';
        }
        cout << "\",\n";
    }
}
