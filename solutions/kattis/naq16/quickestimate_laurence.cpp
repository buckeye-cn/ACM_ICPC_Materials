#include <iostream>
#include <string>

using namespace std;

int main() {
    int N;
    cin >> N;

    string n;
    for (int i = 0; i < N; i++) {
        cin >> n;
        cout << n.length() << "\n";
    }
}
