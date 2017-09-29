#include <iostream>

using namespace std;

long sum[801][801] = {}; // max(sum) = 10^10
long nodes[1280002] = {};
long update[1920003] = {};

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

	unsigned int n_i = 2;
	for (unsigned int n = 0; n < N; n++) {
		int v_i = V[n][0];
		int v_j = V[n][1];

		unsigned int u_i = 0;
		for (unsigned int i = 0; i < n_i; i += 2) {
			long o_i = nodes[i];
			long o_j = nodes[i+1];
			long d_i = o_i + v_i;
			long d_j = o_j + v_j;
			update[u_i++] = d_i;
			update[u_i++] = d_j;
			update[u_i++] = get_sum(o_i, o_j);
		}

		for (unsigned int i = 0; i < u_i; i += 3) {
			long d_i = update[i];
			long d_j = update[i+1];
			long del = update[i+2];
			long& sum_d = get_sum(d_i, d_j);
			if (sum_d == 0) {
				nodes[n_i++] = d_i;
				nodes[n_i++] = d_j;
			}
			sum_d += del;
		}
	}
	cout << get_sum(0, 0) - 1 << endl;
}
