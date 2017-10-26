#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<char, string> dict = {
        {'a', "@"}, {'b', "8"},
        {'c', "("}, {'d', "|)"},
        {'e', "3"}, {'f', "#"},
        {'g', "6"}, {'h', "[-]"},
        {'i', "|"}, {'j', "_|"},
        {'k', "|<"}, {'l', "1"},
        {'m', "[]\\/[]"}, {'n', "[]\\[]"},
        {'o', "0"}, {'p', "|D"},
        {'q', "(,)"}, {'r', "|Z"},
        {'s', "$"}, {'t', "']['"},
        {'u', "|_|"}, {'v', "\\/"},
        {'w', "\\/\\/"}, {'x', "}{"},
        {'y', "`/"}, {'z', "2"},
    };

    char ch;
    while ((ch = getchar()) != '\n') {
        if ('a' <= ch && ch <= 'z') {
            cout << dict[ch];
        } else if ('A' <= ch && ch <= 'Z') {
            cout << dict[ch - ('A' - 'a')];
        } else {
            cout << ch;
        }
    }
    cout << endl;
}
