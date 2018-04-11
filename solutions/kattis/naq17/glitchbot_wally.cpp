#include <bits/stdc++.h>

using namespace std;

struct Robot {
    int x;
    int y;
    int direction;
};

void move(int inst, Robot & robot)
{
    if (inst == 0) {
        switch(robot.direction) {
        case 0:
            robot.y++;
            break;
        case 1:
            robot.x++;
            break;
        case 2:
            robot.y--;
            break;
        case 3:
            robot.x--;
            break;
        }
    } else if (inst == 1) {
        robot.direction--;
        if (robot.direction == -1) robot.direction = 3;
    } else {
        robot.direction++;
        if (robot.direction == 4) robot.direction = 0;
    }
}

void execute(int start, vector<int> & inst, Robot & robot)
{
    for (size_t i = start; i < inst.size(); i++) {
        move(inst[i], robot);
    }
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    Robot robot = { 0, 0, 0 };
    Robot robot_copy = { 0, 0, 0 };

    int x, y;
    // scanf("%d%d", &x, &y);
    cin >> x >> y;

    int n;
    // scanf("%d", &n);
    cin >> n;

    vector<int> inst(n);
    for (auto i = 0; i < n; ++i) {
        string move;
        cin >> move;
        if (move == "Forward") inst[i] = 0;
        else if (move == "Left") inst[i] = 1;
        else inst[i] = 2;
    }

    for (auto i = 0; i < n; ++i) {
        robot_copy.x = robot.x;
        robot_copy.y = robot.y;
        robot_copy.direction = robot.direction;
        move(0, robot_copy);
        execute(i + 1, inst, robot_copy);
        if (robot_copy.x == x && robot_copy.y == y) {
            cout << i + 1 << " Forward" << "\n";
            break;
        }

        // cerr << robot_copy.x << " "<< robot_copy.y << endl;

        robot_copy.x = robot.x;
        robot_copy.y = robot.y;
        robot_copy.direction = robot.direction;
        move(1, robot_copy);
        execute(i + 1, inst, robot_copy);
        if (robot_copy.x == x && robot_copy.y == y) {
            cout << i + 1 << " Left" << "\n";
            break;
        }

        // cerr << robot_copy.x << " "<< robot_copy.y << endl;

        robot_copy.x = robot.x;
        robot_copy.y = robot.y;
        robot_copy.direction = robot.direction;
        move(2, robot_copy);
        execute(i + 1, inst, robot_copy);
        if (robot_copy.x == x && robot_copy.y == y) {
            cout << i + 1 << " Right" << "\n";
            break;
        }

        // cerr << robot_copy.x << " "<< robot_copy.y << endl;

        move(inst[i], robot);
    }

    return 0;
}
