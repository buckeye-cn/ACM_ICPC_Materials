#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

int X, N, M;
int from, to;
int depth;
uint8_t board[100007][23][53];

int main() {
    int _N;
    scanf("%d", &_N);

    for (int _i = 0; _i < _N; _i++) {
        memset(board, 0, (MAX(depth, X)+1)*23*53);

        scanf("%d %d %d", &X, &N, &M);
        getchar();
        for (int i = 1; i <= M; i++)
            if (getchar() == 'G')
                to = i;
        getchar();
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++)
                if (getchar() == 'X')
                    board[0][i][j] = 3;
            getchar();
        }
        for (int i = 1; i <= M; i++)
            if (getchar() == 'F')
                from = i;
        board[0][N+1][from] = 1;

        for (depth = 1; depth <= X; depth++) {
            for (int i = 0; i <= N+1; i++) {
                for (int j = 1; j <= M; j++) {
                    uint8_t pc = board[depth-1][i][j];
                    if (pc == 1) {
                        board[depth][i][j]   |= 1;
                        //board[depth][i+1][j] |= 1;
                        board[depth][i-1][j] |= 1;
                        board[depth][i][j+1] |= 1;
                        board[depth][i][j-1] |= 1;
                    } else if (pc == 3) {
                        if (~(i ^ N) & 1) board[depth][i][(j+1 > M) ? 1 : j+1] = 3;
                        else              board[depth][i][(j-1 < 1) ? M : j-1] = 3;
                    }
                }
            }
            if (board[depth][0][to])
                break;
        }
        if (depth > X)
            puts("The problem has no solution.");
        else
            printf("The minimum number of turns is %d.\n", depth);
    }
}
