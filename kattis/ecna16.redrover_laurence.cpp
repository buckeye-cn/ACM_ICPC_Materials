#include <algorithm>
#include <iostream>
#include <map>
#include <string>

//#define DEBUG

using namespace std;

string s;
int LEN;
bool EQ[100][100] = {};

void output_eq() {
#ifdef DEBUG
	cerr << "  ";
	for (char c : s) {
		cerr << c << " ";
	}
	cerr << endl;
	for (int i = 0; i < LEN; i++) {
		cerr << s[i] << " ";
		for (int j = 0; j < LEN; j++) {
			cerr << EQ[i][j] << " ";
		}
		cerr << endl;
	}
#endif
}

int main() {
	cin >> s;

	LEN = s.length();

	for (int i = 0; i < LEN; i++)
		for (int j = 0; j < LEN; j++)
			EQ[i][j] = s[i] == s[j];

	output_eq();

	int min_len = LEN;
	for (int len = 2; len < LEN/2; len++) {
		for (int i = 1; i < LEN-len+1; i++) {
			for (int j = 0; j < LEN-len+1; j++) {
				EQ[i][j] &= s[i+len-1] == s[j+len-1];
			}
		}
		output_eq();

		map<string, int> c = {};
		for (int i = 1; i < LEN-len+1; i++) {
			string subs = s.substr(i, len);
			if (c.count(subs)) {
				continue;
			}
			c[subs] = 0;
			int j = 0;
			while (j < LEN-len+1) {
				if (EQ[i][j]) {
					c[subs] += 1;
					j += len;
				} else {
					j += 1;
				}
			}
		}

		if (c.size() == 0) break;

		int max_m = 0;
		for (auto p : c) {
			max_m = max(max_m, p.second);
#ifdef DEBUG
			cerr << p.first << "\t" << p.second << endl;
#endif
		}

		int len_res = LEN - max_m * (len-1) + len;
		min_len = min(min_len, len_res);

#ifdef DEBUG
		cerr << max_m << " " << len_res << endl << "---------" << endl;
#endif
	}

	cout << min_len << endl;
}
