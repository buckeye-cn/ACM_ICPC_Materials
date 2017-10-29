#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int inf = 1e6;

inline bool isinf(int n) { return n >= inf; }

int main() {
	int n_loc;
	cin >> n_loc;

	int LOC[101] = {};
	for (int i = 1; i <= n_loc; i++)
		cin >> LOC[i];

	int n_road;
	cin >> n_road;

	int ROAD[101][101];
	for (int i = 0; i < 101; i++)
		for (int j = 0; j < 101; j++)
			ROAD[i][j] = inf;
	for (int i = 1; i <= n_road; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		ROAD[a][b] = l;
		ROAD[b][a] = l;
	}

	int dis_to[101] = {};
	for (int i = 2; i <= n_loc; i++)
		dis_to[i] = inf;
	int n_packs[101] = { 0, LOC[1] };

	vector<int> unvisited;
	for (int i = n_loc; i >= 1; i--)
		unvisited.push_back(i);

	int current = 1;
	while (true) {
		for (int i = 1; i <= n_loc; i++) {
			int dis_cur_i = ROAD[current][i];
			if (!isinf(dis_cur_i)) {
				int dis_i = dis_to[current] + dis_cur_i;
				if (dis_i < dis_to[i]) {
					dis_to[i] = dis_i;
					n_packs[i] = n_packs[current] + LOC[i];
				} else if (dis_i == dis_to[i]) {
					n_packs[i] = max(n_packs[i], n_packs[current] + LOC[i]);
				}
			}
		}

		for (unsigned long i = 0; i < unvisited.size(); i++) {
			if (unvisited[i] == current) {
				unvisited.erase(unvisited.begin()+i);
				break;
			}
		}

		if (current == n_loc) {
			break;
		}

		int min_loc = 0;
		int min_dis = inf;
		for (int loc : unvisited) {
			if (dis_to[loc] < min_dis) {
				min_loc = loc;
				min_dis = dis_to[loc];
			}
		}
		if (isinf(min_dis)) {
			break;
		}
		current = min_loc;
	}

	if (!isinf(dis_to[n_loc])) {
		cout << dis_to[n_loc] << " " << n_packs[n_loc] << endl;
	} else {
		cout << "impossible" << endl;
	}
}
