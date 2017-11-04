// https://open.kattis.com/problems/foosball

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    string names[10];
    for (int i = 0; i < n; ++i) {
        cin >> names[i];
    }

    string result;
    cin >> result;

    string play[2][2] {{names[0], names[2]}, {names[1], names[3]}};

    queue<string> wait;
    for (int i = 4; i < n; ++i) {
        wait.push(names[i]);
    }

    char winner = '?';
    int win = 0;
    int best = 0;
    vector<pair<string, string>> bests;
    for (int i = 0; i < result.size(); ++i) {
        // cout << play[0][0] << ' ' << play[0][1] << ' ' << play[1][0] << ' ' << play[1][1] << endl;

        int g = (result[i] == 'W' ? 0 : 1);

        if (result[i] == winner) {
            wait.push(play[g ^ 1][1]);
            play[g ^ 1][1] = play[g ^ 1][0];
            play[g ^ 1][0] = wait.front();
            wait.pop();

            win += 1;
        } else {
            wait.push(play[g ^ 1][(win & 1) ^ 1]);
            play[g ^ 1][1] = play[g ^ 1][win & 1];
            play[g ^ 1][0] = wait.front();
            wait.pop();

            winner = result[i];
            win = 1;
        }

        if (win > best) {
            bests.clear();
            best = win;
            if (win - 1 == i) {
                bests.push_back({play[g][0], play[g][1]});
            } else {
                bests.push_back({play[g][1], play[g][0]});
            }
        } else if (win == best) {
            bests.push_back({play[g][1], play[g][0]});
        }
    }

    for (auto i: bests) {
        cout << i.first << ' ' << i.second << endl;
    }

    return 0;
}
