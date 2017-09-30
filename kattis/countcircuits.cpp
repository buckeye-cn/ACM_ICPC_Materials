#include <iostream>

using namespace std;

long sum[801][801] = {}; // max(sum) = 10^10
long nodes[801*801][2] = {};
long update[801*801][3] = {};

inline long& get_sum(int i, int j) {
	return sum[i + 400][j + 400];
}

int main() {
	get_sum(0, 0) = 1;

	unsigned int N;
	cin >> N;

	int V[50][2] = {};
	for (unsigned int i = 0; i < N; i++)
		cin >> V[i][0] >> V[i][1];

	unsigned int n_i = 1;
	for (unsigned int n = 0; n < N; n++) {
		int v_i = V[n][0];
		int v_j = V[n][1];

		unsigned int u_i = 0;
		for (unsigned int i = 0; i < n_i; i++) {
			long o_i = nodes[i][0];
			long o_j = nodes[i][1];
			long d_i = o_i + v_i;
			long d_j = o_j + v_j;
			update[u_i][0] = d_i;
			update[u_i][1] = d_j;
			update[u_i][2] = get_sum(o_i, o_j);
			u_i++;
		}

		for (unsigned int i = 0; i < u_i; i++) {
			long d_i = update[i][0];
			long d_j = update[i][1];
			long del = update[i][2];
			long& sum_d = get_sum(d_i, d_j);
			if (sum_d == 0) {
				nodes[n_i][0] = d_i;
				nodes[n_i][1] = d_j;
				n_i++;
			}
			sum_d += del;
		}
	}
	cout << get_sum(0, 0) - 1 << endl;
}
