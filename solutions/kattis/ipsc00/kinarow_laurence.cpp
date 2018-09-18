#include <array>
#include <iostream>

using namespace std;

array<array<char, 205>, 205> board;

int wx = 0, wo = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int L;
    cin >> L;

    for (int gi = 0; gi < L; gi++) {
        for (auto& l : board) {
            l.fill('.');
        }

        int M, N, K;
        cin >> N >> M >> K;
        cin.get();

        for (int i = 1; i <= M; i++) {
            for (int j = 1; j <= N; j++) {
                board[i][j] = cin.get();
            }
            cin.get();
        }

        for (int i = 1; i <= M; i++) {
            for (int j = 1; j <= N; j++) {
                char c = board[i][j];
                if (c != '.') {
#define CHECK(di, dj) \
                    if (board[i-di][j-dj] != c) { \
                        int count = 1, _i = i, _j = j; \
                        while (1 <= _i && _i <= M && 1 <= _j && _j <= N) { \
                            _i += di; _j += dj; \
                            if (board[_i][_j] == c) { \
                                count++; \
                            } else { \
                                break; \
                            } \
                        } \
                        if (count >= K) { \
                            switch (c) { \
                                case 'o': wo++; goto EL; \
                                case 'x': wx++; goto EL; \
                            } \
                        } \
                    } \

                    CHECK(1, 0);
                    CHECK(-1, 1);
                    CHECK(0, 1);
                    CHECK(1, 1);

#undef CHECK
                }
            }
EL:
            continue;
        }
    }

    cout << wx << ':' << wo << '\n';
}
