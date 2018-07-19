// https://open.kattis.com/problems/twentyfour

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define ADD -1
#define MUL -2
#define ANY -3

#define OP_ADD -11
#define OP_SUB -12
#define OP_MUL -13
#define OP_DIV -14

using namespace std;

int a, b, c, d;
int best = 1 << 30;

int calc(int *data) {
    int stack[4] = {};
    int stack_size = 0;

    for (int i = 0; i < 7; ++i) {
        switch (data[i]) {
            case OP_ADD:
                stack[stack_size - 2] += stack[stack_size - 1];
                stack_size -= 1;
                break;
            case OP_SUB:
                stack[stack_size - 2] -= stack[stack_size - 1];
                stack_size -= 1;
                break;
            case OP_MUL:
                stack[stack_size - 2] *= stack[stack_size - 1];
                stack_size -= 1;
                break;
            case OP_DIV:
                if (!stack[stack_size - 1]) return -1;
                if (stack[stack_size - 2] % stack[stack_size - 1]) return -1;
                stack[stack_size - 2] /= stack[stack_size - 1];
                stack_size -= 1;
                break;
            default:
                stack[stack_size] = data[i];
                stack_size += 1;
                break;
        }
    }

    return stack[0];
}

void iter_operator(int score, int aa, int bb, int cc, int dd, int ee, int ff, int gg) {
    int data[7] = {aa, bb, cc, dd, ee, ff, gg};

    int i1, i2, i3;
    for (i1 = 0; data[i1] > 0; ++i1);
    for (i2 = i1 + 1; data[i2] > 0; ++i2);
    for (i3 = i2 + 1; data[i3] > 0; ++i3);

    for (int j1 = OP_DIV; j1 <= OP_ADD; ++j1)
    for (int j2 = OP_DIV; j2 <= OP_ADD; ++j2)
    for (int j3 = OP_DIV; j3 <= OP_ADD; ++j3) {
        if (data[i1] == ADD && j1 != OP_ADD && j1 != OP_SUB) continue;
        if (data[i1] == MUL && j1 != OP_MUL && j1 != OP_DIV) continue;
        if (data[i2] == ADD && j2 != OP_ADD && j2 != OP_SUB) continue;
        if (data[i2] == MUL && j2 != OP_MUL && j2 != OP_DIV) continue;
        if (data[i3] == ADD && j3 != OP_ADD && j3 != OP_SUB) continue;
        if (data[i3] == MUL && j3 != OP_MUL && j3 != OP_DIV) continue;

        int data2[7] = {aa, bb, cc, dd, ee, ff, gg};
        data2[i1] = j1;
        data2[i2] = j2;
        data2[i3] = j3;

        // for (int i = 0; i < 7; ++i) {
        //     cerr << data2[i] << ' ';
        // }
        // cerr << endl;
        // cerr << calc(data2) << endl;

        if (calc(data2) == 24) {
            if (best > score) best = score;
        }
    }
}

void iter_parentheses_1_0(int score, int aa, int bb, int cc, int dd, int o1, int o2) {
    iter_operator(score, aa, bb, ANY, cc, o1, dd, o2); // (ab)cd
    iter_operator(score, aa, bb, o1, cc, o2, dd, ANY); // (abc)d
    // iter_operator(score, aa, bb, ANY, cc, dd, o1, o2); // (ab)cd
    iter_operator(score, aa, bb, o1, cc, dd, ANY, o2); // ab(cd)
    iter_operator(score, aa, bb, cc, ANY, o1, dd, o2); // a(bc)d
    // iter_operator(score, aa, bb, cc, o1, o2, dd, ANY); // (abc)d
    // iter_operator(score, aa, bb, cc, ANY, dd, o1, o2); // a(bc)d
    iter_operator(score, aa, bb, cc, o1, dd, o2, ANY); // a(bcd)
    // iter_operator(score, aa, bb, cc, dd, ANY, o1, o2); // ab(cd)
    // iter_operator(score, aa, bb, cc, dd, o1, o2, ANY); // a(bcd)
}

void iter_parentheses_1_1(int score, int aa, int bb, int cc, int dd, int o1, int o2) {
    // iter_operator(score, aa, bb, ANY, cc, o1, dd, o2); // (ab)cd
    // iter_operator(score, aa, bb, o1, cc, o2, dd, ANY); // (abc)d
    iter_operator(score, aa, bb, ANY, cc, dd, o1, o2); // (ab)cd
    // iter_operator(score, aa, bb, o1, cc, dd, ANY, o2); // ab(cd)
    // iter_operator(score, aa, bb, cc, ANY, o1, dd, o2); // a(bc)d
    iter_operator(score, aa, bb, cc, o1, o2, dd, ANY); // (abc)d
    iter_operator(score, aa, bb, cc, ANY, dd, o1, o2); // a(bc)d
    // iter_operator(score, aa, bb, cc, o1, dd, o2, ANY); // a(bcd)
    iter_operator(score, aa, bb, cc, dd, ANY, o1, o2); // ab(cd)
    iter_operator(score, aa, bb, cc, dd, o1, o2, ANY); // a(bcd)
}

void iter_parentheses_2(int score, int aa, int bb, int cc, int dd) {
    iter_operator(score, aa, bb, ANY, cc, ANY, dd, ANY); // ((ab)c)d
    iter_operator(score, aa, bb, ANY, cc, dd, ANY, ANY); // (ab)(cd)
    iter_operator(score, aa, bb, cc, ANY, ANY, dd, ANY); // (a(bc))d
    iter_operator(score, aa, bb, cc, ANY, dd, ANY, ANY); // a((bc)d)
    iter_operator(score, aa, bb, cc, dd, ANY, ANY, ANY); // a(b(cd))
}

void iter_parentheses(int score, int aa, int bb, int cc, int dd) {
    iter_operator(score, aa, bb, MUL, cc, MUL, dd, MUL);
    iter_operator(score, aa, bb, MUL, cc, MUL, dd, ADD);
    iter_operator(score, aa, bb, MUL, cc, ADD, dd, ADD);
    iter_operator(score, aa, bb, ADD, cc, ADD, dd, ADD);
    iter_operator(score, aa, bb, MUL, cc, dd, MUL, ADD);
    iter_operator(score, aa, bb, ADD, cc, dd, MUL, ADD);
    iter_operator(score, aa, bb, cc, MUL, ADD, dd, ADD);
    iter_operator(score, aa, bb, cc, MUL, dd, MUL, ADD);

    iter_parentheses_1_0(score + 1, aa, bb, cc, dd, MUL, MUL);
    iter_parentheses_1_0(score + 1, aa, bb, cc, dd, MUL, ADD);
    iter_parentheses_1_0(score + 1, aa, bb, cc, dd, ADD, ADD);
    iter_parentheses_1_1(score + 1, aa, bb, cc, dd, MUL, ADD);
    iter_parentheses_2(score + 2, aa, bb, cc, dd);
}

void iter_order(int score) {
    iter_parentheses(score + 0, a, b, c, d);
    iter_parentheses(score + 2, a, b, d, c);
    iter_parentheses(score + 2, a, c, b, d);
    iter_parentheses(score + 4, a, c, d, b);
    iter_parentheses(score + 4, a, d, b, c);
    iter_parentheses(score + 6, a, d, c, b);

    iter_parentheses(score + 2, b, a, c, d);
    iter_parentheses(score + 4, b, a, d, c);
    iter_parentheses(score + 4, b, c, a, d);
    iter_parentheses(score + 6, b, c, d, a);
    iter_parentheses(score + 6, b, d, a, c);
    iter_parentheses(score + 8, b, d, c, a);

    iter_parentheses(score + 4, c, a, b, d);
    iter_parentheses(score + 6, c, a, d, b);
    iter_parentheses(score + 6, c, b, a, d);
    iter_parentheses(score + 8, c, b, d, a);
    iter_parentheses(score + 8, c, d, a, b);
    iter_parentheses(score + 10, c, d, b, a);

    iter_parentheses(score + 6, d, a, b, c);
    iter_parentheses(score + 8, d, a, c, b);
    iter_parentheses(score + 8, d, b, a, c);
    iter_parentheses(score + 10, d, b, c, a);
    iter_parentheses(score + 10, d, c, a, b);
    iter_parentheses(score + 12, d, c, b, a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> a >> b >> c >> d;

    iter_order(0);

    if (best < 1 << 30) {
        cout << best << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
