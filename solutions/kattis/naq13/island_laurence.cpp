#include <cstring>
#include <iostream>

using namespace std;

char board[3][83][83];

inline bool is_not_ocean(char c) {
    return c == 'X'|| c == '#' || c == 'B' ;
}

inline bool is_land(char c) {
    return c == 'X' || c == '#';
}

inline bool can_move(char c1, char c2) {
    switch (c1) {
        case 'X': return true;
        case '#': return c2 != 'B';
        case 'B': return c2 != '#';
        default: return false;
    }
}

void dfs_bus(int i, int j) {
    board[2][i][j] = 1;
    auto dfs = [=](int _i, int _j) {
        if (is_not_ocean(board[0][_i][_j]) && board[2][_i][_j] == 0)
            if (can_move(board[0][i][j], board[0][_i][_j]))
                dfs_bus(_i, _j);
    };
    dfs(i-1, j);
    dfs(i+1, j);
    dfs(i, j-1);
    dfs(i, j+1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int testcase = 1;

    while (cin.good()) {
        memset(board, 0, sizeof(board));

        int row = 0, col = 0;

        string line;
        while (getline(cin, line)) {
            if (line.empty())
                break;
            row++;
            for (int i = 1; i <= (int)line.length(); i++)
                board[0][row][i] = line.at(i-1);
            col = line.length();
        }

        int island = 0, bridge = 0, bus = 0;

        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                if (is_land(board[0][i][j]) && board[1][i][j] == 0) {
                    for (int _i = i; _i <= row; _i++) {
                        if (!is_land(board[0][_i][j]))
                            break;
                        for (int _j = j; _j <= col; _j++) {
                            if (!is_land(board[0][_i][_j]))
                                break;
                            board[1][_i][_j] = 1;
                        }
                    }
                    island++;
                }
                if (board[0][i][j] == 'X') {
                    bridge += board[0][i][j+1] == 'B';
                    bridge += board[0][i+1][j] == 'B';
                }
                if (is_not_ocean(board[0][i][j]) && board[2][i][j] == 0) {
                    dfs_bus(i, j);
                    bus++;
                }
            }
        }

        cout << "Map " << testcase++ << endl;
        cout << "islands: " << island << endl;
        cout << "bridges: " << bridge << endl;
        cout << "buses needed: " << bus << endl;
        cout << endl;
    }
}
