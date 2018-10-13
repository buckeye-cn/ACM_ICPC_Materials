#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    char ed;

    ed = cin.get();
    cin.get();

    if (ed == 'E') {
        char c = cin.get();
        while (c != '\n') {
            int count = 0;
            char c1 = c;
            for (; c == c1; c = cin.get(), count++) {}
            cout << c1 << count;
        }
        cout << endl;
    } else {
        for (;;) {
            char c = cin.get();
            int n = cin.get()-'0';
            if (c == '\n')
                break;
            for (int i = 0; i < n; i++)
                cout << c;
        }
        cout <<'\n';
    }
}
