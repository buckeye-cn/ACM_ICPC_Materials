#include <iostream>

using namespace std;

char TABLE[27][27] = {};

constexpr inline int c2v(char c) {
	return (c == ' ') ? 0 : c-'a'+1;
}

constexpr inline char v2c(int v) {
	return (v == 0) ? ' ' : 'a'+v-1;
}

inline void testcase() {
	char ed;
	cin >> ed;

	char line[100] = {};

	cin.ignore(1, ' ');
	cin.getline(line, 100);

	if (ed == 'e') {
		char last = line[0];
		cout << last;
		for (int i = 1; i < 100; i++) {
			if (line[i] == '\0') break;
			last = TABLE[c2v(line[i])][c2v(last)];
			cout << last;
		}
	} else {
		cout << line[0];
		for (int i = 1; i < 100; i++) {
			if (line[i] == '\0') break;
			for (int j = 0; j <= 26; j++) {
				if (TABLE[j][c2v(line[i-1])] == line[i]) {
					cout << v2c(j);
					break;
				}
			}
		}
	}
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.precision(10);

	for (int i = 0; i <= 26; i++)
		for (int j = 0; j <= 26; j++)
			TABLE[i][j] = v2c((i+j) % 27);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) testcase();
}
