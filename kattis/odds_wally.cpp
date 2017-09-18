#include <iostream>

using namespace std;

bool has_mia(char p[]) {
    return (p[0] == '2' && p[1] == '1') || (p[0] == '1' && p[1] == '2');
}

bool only_star(char p[]) {
    return p[0] == '*' && p[1] == '*';
}

bool has_star(char p[]) {
    return p[0] == '*' || p[1] == '*';
}

bool is_pair(char p[]) {
    return p[0] == p[1];
}

void sort_pair(char p[]) {
    if (has_star(p) && !only_star(p)) {
        if (p[0] == '*') {
            char temp = p[0];
            p[0] = p[1];
            p[1] = temp;
        }
    }
    else if (p[0] < p[1]) {
        char temp = p[0];
        p[0] = p[1];
        p[1] = temp;
    }
}

int main() {
    char p1[2];
    char p2[2];

    while (true) {
        cin >> p1[0] >> p1[1];
        cin >> p2[0] >> p2[1];

        if (p1[0] == '0') {
            return 0;
        }
        sort_pair(p1);
        sort_pair(p2);
        if (has_mia(p2)) {
            cout << 0 << endl;
        } else if (has_mia(p1)) {
            if (only_star(p2)) {
                cout << "17/18" << endl;
            } else if (!has_star(p2) && !has_mia(p2)) {
                cout << 1 << endl;
            } else if (p2[0] == '1' || p2[0] == '2') {
                cout << "5/6" << endl;
            }
            // } else {
            //     cout << "TODO" << endl;
            // }
        } else if (only_star(p1) && only_star(p2)) {
            cout << "205/432" << endl;
        } else {
            if (p1[0] != '*' && p1[1] != '*' && p2[0] != '*' && p2[1] != '*') {
                if (is_pair(p1) && !is_pair(p2)) {
                    cout << 1 << endl;
                } else if (!is_pair(p1) && is_pair(p2)) {
                    cout << 0 << endl;
                } else {
                    // if (p1[0] < p1[1]) {
                    //     char temp = p1[0];
                    //     p1[0] = p1[1];
                    //     p1[1] = temp;
                    // }
                    // if (p2[0] < p2[1]) {
                    //     char temp = p2[0];
                    //     p2[0] = p2[1];
                    //     p2[1] = temp;
                    // }
                    int s1 = (p1[0] - '0') * 10 + (p1[1] - '0');
                    int s2 = (p2[0] - '0') * 10 + (p2[1] - '0');
                    if (s1 <= s2) {
                        cout << 0 << endl;
                    } else {
                        cout << 1 << endl;
                    }    
                }
            } else {
                if (is_pair(p1)) {
                    if (only_star(p2)) {
                        
                    }
                }
                cout << "TODO" << endl;
            }
        }
    }

    return 0;
}
