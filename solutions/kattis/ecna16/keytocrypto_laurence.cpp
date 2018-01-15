#include <iostream>
#include <string>

using namespace std;

char key[1002] = {};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string ct, sw;
    cin >> ct >> sw;

    sw.copy(key, sw.size());

    for (uint16_t i = 0; i < ct.size(); i++) {
        char c = ct[i] - (key[i] - 'A');
        c = (c < 'A') ? c + 26 : c;
        key[sw.size() + i] = c;
        cout << c;
    }
    cout << endl;
}
