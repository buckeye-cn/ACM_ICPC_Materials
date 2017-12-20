#include <iostream>
#include <string>

using namespace std;

bool setQueen(int x, int y, int matrix[8][8]) {
    matrix[x][y] = 2;
    for (auto i = 0; i < 8; ++i) {
        if (i != x) {
            if (matrix[i][y] == 2) {
                return false;
            }
        }
    }

    for (auto i = 0; i < 8; ++i) {
        if (i != y) {
            if (matrix[x][i] == 2) {
                return false;
            }
        }
    }

    for (auto i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j) {
        if (matrix[i][j] == 2) {
            return false;
        }
    }

    for (auto i = x + 1, j = y + 1; i < 8 && j < 8; ++i, ++j) {
        if (matrix[i][j] == 2) {
            return false;
        }
    }

    for (auto i = x - 1, j = y + 1; i >= 0 && j < 8; --i, ++j) {
        if (matrix[i][j] == 2) {
            return false;
        }
    }

    for (auto i = x - 1, j = y + 1; i >= 0 && j < 8; --i, ++j) {
        if (matrix[i][j] == 2) {
            return false;
        }
    }

    return true;
}

void print_matrix(int matrix[8][8]) {
    for (auto i = 0; i < 8; ++i) {
        for (auto j = 0; j < 8; ++j) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

int main() {
    int matrix[8][8] = {};
    int count = 0;

    for (int i = 0; i < 8; ++i) {
        string line;
        cin >> line;
        for (int j = 0; j < 8; ++j) {
            if (line[j] == '*') {
                count++;
                if (!setQueen(i, j, matrix)) {
                    // cout << "Line" << i << endl;
                    // print_matrix(matrix);
                    cout << "invalid" << endl;
                    return 0;
                }
            }
        }
    }

    if (count != 8) {
        cout << "invalid" << endl;
    } else {
        cout << "valid" << endl;
    }

    return 0;
}
