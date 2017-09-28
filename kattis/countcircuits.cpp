#include <iostream>
#include <vector>

using namespace std;

long sum[1024][1024] = {}; // max 10^10

inline long* get_sum(int i, int j) {
	return &sum[i + 400][j + 400];
}

int main() {
	*get_sum(0, 0) = 1;

	int N;
	cin >> N;

	int V[50][2] = {};
	long sum_i = 0, sum_j = 0;
	for (int i = 0; i < N; i++) {
		int v_i, v_j;
		cin >> v_i >> v_j;
		V[i][0] = v_i; V[i][1] = v_j;
		sum_i += v_i; sum_j += v_j;
	}

	vector<int> nodes;
	nodes.push_back(0);
	nodes.push_back(0);
	for (int n = 0; n < N; n++) {
		int v_i = V[n][0];
		int v_j = V[n][1];

		vector<long> update;
		int len = nodes.size();
		for (int i = 0; i < len; i += 2) {
			int o_i = nodes[i];
			int o_j = nodes[i+1];
			int d_i = o_i + v_i;
			int d_j = o_j + v_j;
			update.push_back(d_i);
			update.push_back(d_j);
			update.push_back(*get_sum(o_i, o_j));
		}

		for (int i = 0; i < update.size(); i += 3) {
			long d_i = update[i];
			long d_j = update[i+1];
			long del = update[i+2];
			auto sum_d = get_sum(d_i, d_j);
			if (*sum_d == 0) {
				nodes.push_back(d_i);
				nodes.push_back(d_j);
			}
			*sum_d += del;
		}
	}
	cout << *get_sum(sum_i, sum_j) - 1 << endl;
}
