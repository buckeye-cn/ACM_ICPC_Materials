#include <iostream>

using namespace std;

int LINE = 0;
int MAX_DEPTH = 0;

int16_t board[7][7];

int dp(int depth = 1) {
    bool ok = false; int diff = -1e9;
    int i, j;
    auto test = [&](int di, int dj) {
        auto &v1r = board[i+di][j+dj], &v2r = board[i+di*2][j+dj*2];
        if (v1r && v2r) {
            auto v1 = v1r, v2 = v2r;
            board[i][j] = v2; v1r = 0; v2r = 0;
            ok = true;
            diff = max(diff, v1 * v2 - (depth >= MAX_DEPTH ? 0 : dp(depth + 1)));
            board[i][j] = 0; v1r = v1; v2r = v2;
        }
    };
    for (i = 1; i <= LINE; i++) {
        for (j = 1; j <= i; j++) {
            if (!board[i][j]) {
                test(-1, -1);
                test(-1, 0);
                test(0, -1);
                test(0, 1);
                test(1, 0);
                test(1, 1);
            }
        }
    }
    return ok ? diff : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 1; ; i++) {
        for (int j = 1; j <= i; j++) {
            int16_t x;
            cin >> x;
            if (!cin.good()) {
                LINE = i - 1;
                MAX_DEPTH--;
                goto RE;
            }
            board[i][j] = x;
            MAX_DEPTH++;
        }
    }
RE:
    cout << dp() << endl;
}
