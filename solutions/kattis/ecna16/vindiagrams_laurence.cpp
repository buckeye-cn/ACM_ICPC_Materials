#include <iostream>

using namespace std;

int N, M;
char map[103][103] = {};

void output() {
    for (int i = 0; i <= N+1; i++) {
        for (int j = 0; j <= M+1; j++)
            if (map[i][j] == '\0')
                cout << " " << " ";
            else
                cerr << map[i][j] << " ";
        cerr << endl;
    }
}

bool is_isec(int i, int j) {
    return (map[i][j] != '\0' && map[i-1][j] != '\0' && map[i+1][j] != '\0' && map[i][j-1] != '\0' && map[i][j+1] != '\0');
}

void mark(int ai, int aj, char ch) {
    int del_i = 0, del_j = -1;
    while (true) {
        int di = ai+del_i;
        int dj = aj+del_j;
        char& c = map[di][dj];
        if (is_isec(di, dj)) {
            ai += del_i;
            aj += del_j;
        } else {
            if (c == ch) {
                break;
            } else if (c == 'X') {
                c = ch;
                ai += del_i;
                aj += del_j;
            } else {
                if (map[ai+1][aj] == 'X') {
                    del_i = 1; del_j = 0;
                } else if (map[ai-1][aj] == 'X') {
                    del_i = -1; del_j = 0;
                } else if (map[ai][aj+1] == 'X') {
                    del_i = 0; del_j = 1;
                } else if (map[ai][aj-1] == 'X') {
                    del_i = 0; del_j = -1;
                } else {
                    break;
                }
            }
        }
    }
}

void flip_ab(char& c, char ab) {
    c ^= 1 << (ab-'A');
}

int main() {
    cin >> N >> M;

    int ai, aj, bi, bj;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            char c;
            cin >> c;
            if (c == 'A') {
                ai = i; aj = j;
            } else if (c == 'B') {
                bi = i; bj = j;
            }
            map[i][j] = (c == '.') ? '\0' : c;
        }
    }

    mark(ai, aj, 'A');
    mark(bi, bj, 'B');

    output();

    for (int i = 0; i <= N; i++) {
        char c = '0';
        for (int j = 0; j <= M; j++) {
            char& cc = map[i][j];
            if (cc == '\0') {
                cc = c;
            } else if (cc == 'A' || cc == 'B') {
                if (map[i][j+1] == cc) {
                    bool up = map[i-1][j] == cc;
                    while (j <= M) {
                        if (map[i][j+1] == cc) {
                            j++;
                        } else if (map[i][j+1] == 'X') {
                            flip_ab(c, (cc == 'A') ? 'B' : 'A');
                            j++;
                        } else {
                            break;
                        }
                    }
                    if ((map[i-1][j] == cc) != up) {
                        flip_ab(c, cc);
                    }
                } else {
                    flip_ab(c, cc);
                }
            }
        }
    }

    int a_c = 0, b_c = 0, c_c = 0;
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            switch (map[i][j]) {
                case '1':
                    a_c++; break;
                case '2':
                    b_c++; break;
                case '3':
                    c_c++; break;
            }
        }
    }

    output();

    cout << a_c << " " << b_c << " " << c_c << endl;
}
