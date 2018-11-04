#include <bits/stdc++.h>

using namespace std;

struct {
    int usa;
    int rec;
} jim[10];

struct {
    int usa;
    int rec;
    int start;
    bool first = 1;
} other[10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 0; i < 10; i++) {
        cin >> jim[i].usa >> jim[i].rec;
    }
    for (int i = 0; i < 10; i++) {
        cin >> other[i].usa >> other[i].rec >> other[i].start;
    }

    long t = 0;

    for (int r = 0; r < 3; r++)
    for (int i = 0; i < 10; i++) {
        int toffset = t - other[i].start;
        if (toffset < 0) {
            t += jim[i].usa;
            if (t > other[i].start) {
                other[i].start = t;
            }
            t += jim[i].rec;
        } else {
            int tused = toffset % (other[i].usa + other[i].rec);
            if (tused < other[i].usa) {
                t += other[i].usa - tused;
                t += jim[i].usa;
                if (jim[i].usa > other[i].rec) {
                    other[i].start = t;
                }
                t += jim[i].rec;
            } else {
                t += jim[i].usa;
                if (jim[i].usa > (other[i].usa + other[i].rec)-tused) {
                    other[i].start = t;
                }
                t += jim[i].rec;
            }
        }
    }

    t -= jim[9].rec;

    cout << t << endl;
}
