#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define SWAP(x,y) { typeof(x) _x = x; typeof(y) _y = y; x = _y; y = _x; }

typedef uint8_t Board[25][55];
Board board[2];

int main() {
    int _N;
    scanf("%d", &_N);

    Board *prev = &board[0], *curr = &board[1];

    for (int _i = 0; _i < _N; _i++) {
        memset(board, 0, sizeof(board));

        int X, N, M;
        int to;

        scanf("%d %d %d", &X, &N, &M);
        getchar();

        N += 2;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++)
                switch (getchar()) {
                    case 'G': to = j; break;
                    case 'F': (*curr)[N][j] = 1; break;
                    case 'X': (*curr)[i][j] = 3; break;
                }
            getchar();
        }

        int depth;
        for (depth = 1; depth <= X; depth++) {
            SWAP(prev, curr);
            memset(curr, 0, sizeof(Board));
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= M; j++) {
                    uint8_t pc = (*prev)[i][j];
                    if (pc == 1) {
                        (*curr)[i][j]   |= 1;
                        //(*curr)[i+1][j] |= 1;
                        (*curr)[i-1][j] |= 1;
                        (*curr)[i][j+1] |= 1;
                        (*curr)[i][j-1] |= 1;
                    } else if (pc == 3) {
                        if ((i ^ N) & 1) (*curr)[i][(j+1 > M) ? 1 : j+1] = 3;
                        else             (*curr)[i][(j-1 < 1) ? M : j-1] = 3;
                    }
                }
            }
            if ((*curr)[1][to])
                break;
        }
        if (depth > X)
            puts("The problem has no solution.");
        else
            printf("The minimum number of turns is %d.\n", depth);
    }
}
