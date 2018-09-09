#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int mintp = 5000000;

    int N, B, H, W;
    cin >> N >> B >> H >> W;
    for (int hi = 0; hi < H; hi++) {
        int p;
        cin >> p;
        for (int wi = 0; wi < W; wi++) {
            int avail;
            cin >> avail;
            if (avail >= N) {
                mintp = min(mintp, p * N);
            }
        }
    }

    if (mintp <= B) {
        cout << mintp << endl;
    } else {
        cout << "stay home\n";
    }
}
