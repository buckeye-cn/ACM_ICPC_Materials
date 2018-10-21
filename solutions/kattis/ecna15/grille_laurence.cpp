#include <bits/stdc++.h>

using namespace std;

char board[13][13];
bool grille1[13][13];
bool grille2[13][13];
bool grille3[13][13];
bool grille4[13][13];
int grilleall[13][13];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N;
    cin >> N;

    int count = 0;

    cin.get();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            auto c = cin.get();
            if (c == '.') {
                grille1[i][j] = true;
                grilleall[i][j] += grille1[i][j];
                count++;
            }
        }
        cin.get();
    }
    for (int i = 0, _j = N-1; i < N && _j >= 0; i++, _j--) {
        for (int j = 0, _i = 0; j < N && _i < N; j++, _i++) {
            grille2[_i][_j] = grille1[i][j];
            grilleall[_i][_j] += grille1[i][j];
        }
    }
    for (int i = 0, _i = N-1; i < N && _i >= 0; i++, _i--) {
        for (int j = 0, _j = N-1; j < N && _j >= 0; j++, _j--) {
            grille3[_i][_j] = grille1[i][j];
            grilleall[_i][_j] += grille1[i][j];
        }
    }
    for (int i = 0, _j = 0; i < N && _j < N; i++, _j++) {
        for (int j = 0, _i = N-1; j < N && _i >= 0; j++, _i--) {
            grille4[_i][_j] = grille1[i][j];
            grilleall[_i][_j] += grille1[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grilleall[i][j] != 1) {
                cout << "invalid grille\n";
                return 0;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grille1[i][j]) {
                board[i][j] = cin.get();
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grille2[i][j]) {
                board[i][j] = cin.get();
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grille3[i][j]) {
                board[i][j] = cin.get();
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grille4[i][j]) {
                board[i][j] = cin.get();
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j];
        }
    }
    cout << '\n';
}
