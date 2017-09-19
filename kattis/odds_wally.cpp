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

bool has_pair(char p[]) {
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

bool win(char s0, char s1, char r0, char r1) {
    char p1[] = {s0, s1};
    char p2[] = {r0, r1};
    sort_pair(p1);
    sort_pair(p2);
    if (has_mia(p1) && !has_mia(p2)) {
        return true;
    } else if (!has_mia(p1) && has_mia(p2)) {
        return false;
    } else if (has_mia(p1) && has_mia(p2)) {
        return false;
    } else if (has_pair(p1) && !has_pair(p2)) {
        return true;
    } else if (!has_pair(p1) && has_pair(p2)) {
        return false;
    } else if (has_pair(p1) && has_pair(p2)) {
        return s0 > r0;
    } else {
        int a = (p1[0] - '0') * 10 + (p1[1] - '0');
        int b = (p2[0] - '0') * 10 + (p2[1] - '0');
        return a > b;
    }
}

int gcd(int a, int b) {
    // int t = b % a;
    int t;
    do {
        t = b % a;
        b = a;
        a = t;
    } while (t != 0);

    return b;
}

void print(int a, int b) {
    if (a == 0) {
        cout << a << endl;
    } else if (a == b) {
        cout << 1 << endl;
    } else {
        int c = gcd(a, b);
        cout << a/c << "/" << b/c << endl;
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
            } else {
                int count = 0;
                for (auto i = '1'; i <= '6'; ++i) {
                    if (win(p1[0], p1[1], p2[0], i)) {
                        count++;
                    }
                }
                print(count, 6);
                // cout << count << "/6" << endl;
            }
        } else if (only_star(p1) && only_star(p2)) {
            cout << "205/432" << endl;
        } else {
            if (p1[0] != '*' && p1[1] != '*' && p2[0] != '*' && p2[1] != '*') {
                cout << win(p1[0], p1[1], p2[0], p2[1]) << endl;
            } else if (!has_star(p1) && only_star(p2)) {
                int count = 0;
                for (auto i = '1'; i <= '6'; ++i) {
                    for (auto j = '1'; j <= '6'; ++j) {
                        if (win(p1[0], p1[1], i, j)) {
                            // cout << p1[0] << " " << p1[1] << " " << i << " " << j << endl;
                            count++;
                        }
                    }
                }
                print(count, 36);
                // cout << count << "/36" << endl;
            } else if (!has_star(p1) && has_star(p2)) {
                int count = 0;
                for (auto i = '1'; i <= '6'; ++i) {
                    if (win(p1[0], p1[1], p2[0], i)) {
                        // cout << p1[0] << " " << p1[1] << " " << p2[0] << " " << i << endl;
                        count++;
                    }
                }
                print(count, 6);
                // cout << count << "/6" << endl;
            } else if (only_star(p1) && !has_star(p2)) {
                int count = 0;
                for (auto i = '1'; i <= '6'; ++i) {
                    for (auto j = '1'; j <= '6'; ++j) {
                        if (win(i, j, p2[0], p2[1])) {
                            // cout << i << " " << j << " " << p2[0] << " " << p2[1] << endl;
                            count++;
                        }
                    }
                }
                print(count, 36);
                // cout << count << "/36" << endl;
            } else if (has_star(p1) && !has_star(p2)) {
                int count = 0;
                for (auto i = '1'; i <= '6'; ++i) {
                    if (win(p1[0], i, p2[0], p2[1])) {
                        // cout << p1[0] << " " << i << " " << p2[0] << " " << p2[1] << endl;
                        count++;
                    }
                }
                print(count, 6);
                // cout << count << "/6" << endl;
            } else if (only_star(p1) && has_star(p2)) {
                int count = 0;
                for (auto i = '1'; i <= '6'; ++i) {
                    for (auto j = '1'; j <= '6'; ++j) {
                        for (auto k = '1'; k <= '6'; ++k) {
                            if (win(i, j, p2[0], k)) {
                                count++;
                            }
                        }
                    }
                }
                print(count, 216);
                // cout << count <<  "/216" << endl;
            } else if (has_star(p1) && only_star(p2)) {
                int count = 0;
                for (auto i = '1'; i <= '6'; ++i) {
                    for (auto j = '1'; j <= '6'; ++j) {
                        for (auto k = '1'; k <= '6'; ++k) {
                            if (win(p1[0], i, j, k)) {
                                count++;
                            }
                        }
                    }
                }
                print(count, 216);
                // cout << count <<  "/216" << endl;
            } else {
                int count = 0;
                for (auto i = '1'; i <= '6'; ++i) {
                    for (auto j = '1'; j <= '6'; ++j) {
                        if (win(p1[0], i, p2[0], j)) {
                            count++;
                        }
                    }
                }
                print(count, 36);
                // cout << count << "/36" << endl;
            }
        }
    }

    return 0;
}
