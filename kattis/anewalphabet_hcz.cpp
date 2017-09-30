// https://open.kattis.com/problems/anewalphabet

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char cmap[64][8] = {
    {64}, "@", "8", "(", "|)", "3", "#", "6",
    "[-]", "|", "_|", "|<", "1", "[]\\/[]", "[]\\[]", "0",
    "|D", "(,)", "|Z", "$", "']['", "|_|", "\\/", "\\/\\/",
    "}{", "`/", "2", {91}, {92}, {93}, {94}, {95},
    {96}, "@", "8", "(", "|)", "3", "#", "6",
    "[-]", "|", "_|", "|<", "1", "[]\\/[]", "[]\\[]", "0",
    "|D", "(,)", "|Z", "$", "']['", "|_|", "\\/", "\\/\\/",
    "}{", "`/", "2", {123}, {124}, {125}, {126}, {127},
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int ch = getchar(); ch >= 0; ch = getchar()) {
        if (ch < 64) {
            cout << char(ch);
        } else {
            cout << (char *) cmap[ch - 64];
        }
    }
    cout << endl;

    return 0;
}
