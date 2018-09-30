#include <iostream>
#include <vector>

#define SQ(x) ((x)*(x))

using namespace std;

struct Rectangle {
    int x1, y1, x2, y2;
};

struct Circle {
    int x, y, d;
};

vector<Rectangle> rectangles;
vector<Circle> circles;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N;

    cin >> N;
    string t;
    for (int i = 0; i < N; i++) {
        cin >> t;
        if (t == "rectangle") {
            Rectangle r;
            cin >> r.x1 >> r.y1 >> r.x2 >> r.y2;
            rectangles.emplace_back(r);
        } else {
            Circle c;
            cin >> c.x >> c.y >> c.d;
            c.d *= c.d;
            circles.emplace_back(c);
        }

    }

    cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        int count = 0;
        for (auto r : rectangles)
            if (r.x1 <= x && x <= r.x2 && r.y1 <= y && y <= r.y2)
                count++;
        for (auto c : circles)
            if (SQ(x-c.x) + SQ(y-c.y) <= c.d)
                count++;
        cout << count << endl;
    }
}
