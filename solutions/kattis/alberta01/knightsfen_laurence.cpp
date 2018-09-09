#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

constexpr array<array<int, 2>, 8> dxy {{
   {{ -2, -1 }},
   {{ -2, 1 }},
   {{ -1, -2 }},
   {{ -1, 2 }},
   {{ 1, -2 }},
   {{ 1, 2 }},
   {{ 2, -1 }},
   {{ 2, 1 }},
}};

array<array<char, 5>, 5> src, dst, orig {{
    {{'1','1','1','1','1'}},
    {{'0','1','1','1','1'}},
    {{'0','0',' ','1','1'}},
    {{'0','0','0','0','1'}},
    {{'0','0','0','0','0'}},
}};

struct {
    int x, y;
} srcsp, dstsp;

int mi;

bool eq() {
    if (srcsp.x != dstsp.x || srcsp.y != dstsp.y)
        return false;
    for (uint8_t i = 0; i < 5; i++)
        for (uint8_t j = 0; j < 5; j++)
            if (src[i][j] != dst[i][j])
                return false;
    return true;
}

bool swapk(int x, int y) {
    if (0 <= srcsp.x + x && srcsp.x + x <= 4 && 0 <= srcsp.y + y && srcsp.y + y <= 4) {
        swap(src[srcsp.x][srcsp.y], src[srcsp.x + x][srcsp.y + y]);
        srcsp.x += x; srcsp.y += y;
        return true;
    } else {
        return false;
    }
}

void solve(int mov = 1) {
   if (mov > 10) {
      return;
   }

   for (auto const& p : dxy) {
       if (swapk(p[0], p[1])) {
           if (eq())
               mi = min(mi, mov);
           else
               solve(mov + 1);
           swapk(-p[0], -p[1]);
       }
   }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N;
    cin >> N;
    cin.get();

    for (int i = 0; i < N; i++) {
        src = orig;
        srcsp.x = 2; srcsp.y = 2;
        mi = 100;

        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                dst[j][k] = cin.get();
                if (dst[j][k] == ' ') {
                    dstsp.x = j; dstsp.y = k;
                }
            }
            cin.get();
        }

        if (eq())
            mi = 0;
        else
            solve();

        if (mi <= 10) {
            cout << "Solvable in " << mi << " move(s).\n";
        } else {
            cout << "Unsolvable in less than 11 move(s).\n";
        }
    }
}
