#include <bits/stdc++.h>

using namespace std;

bool LINK[103][103];

long INF_1[103], INF_0[103];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long N, M, S, T;
    cin >> N >> M >> S >> T;

    for (long i = 0; i < M; i++) {
        long a, b;
        cin >> a >> b;
        LINK[a][b] = true;
        LINK[b][a] = true;
    }

    auto &inf0 = INF_0, &inf1 = INF_1;
    inf1[S] = 1;

    for (long t = 1; t <= T; t++) {
        swap(inf0, inf1);
        memset(inf1, 0, sizeof(inf1));
        for (long i = 0; i < N; i++) {
            if (inf0[i]) {
                for (long j = 0; j < N; j++) {
                    if (LINK[i][j]){
                        inf1[j] += inf0[i];
                    }
                }
            }
        }
    }

    long count = 0;
    for (long i = 0; i < N; i++) {
        count += inf1[i];
    }
    cout << count << endl;
}
