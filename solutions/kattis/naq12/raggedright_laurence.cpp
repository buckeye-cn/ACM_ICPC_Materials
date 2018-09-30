#include <iostream>

using namespace std;

string lines[103];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int count = -1, max_len = -1, rag = 0;
    while (getline(cin, lines[++count])) { }
    for (int i = 0; i < count; i++)
        max_len = max(max_len, (int)lines[i].size());
    for (int i = 0; i < count-1; i++) {
        int d = lines[i].size() - max_len;
        rag += d * d;
    }
    cout << rag << endl;
}
