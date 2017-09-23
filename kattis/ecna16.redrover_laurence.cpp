#include <iostream>
#include <map>
#include <string>

//#define DEBUG

using namespace std;

bool EQ[100][100] = {};
int LEN;

void output_eq(string& s) {
#ifdef DEBUG
	cerr << "  ";
	for (char c : s) {
		cerr << c << " ";
	}
	cerr << endl;
	for (int i = 0; i < LEN; i++) {
		cerr << s[i] << " ";
		for (int j = 0; j <= i; j++) {
			cerr << EQ[i][j] << " ";
		}
		cerr << endl;
	}
#endif
}

int main() {
	string s;
	cin >> s;

	LEN = s.length();

	for (int i = 0; i < LEN; i++)
		for (int j = 0; j <= i; j++)
			EQ[i][j] = s[i] == s[j];

	output_eq(s);

	int min = LEN;
	for (int len = 2; len < LEN/2; len++) {
		for (int i = 1; i < LEN-len+1; i++) {
			for (int j = 0; j <= i; j++) {
				EQ[i][j] = EQ[i][j] && (s[i+len-1] == s[j+len-1]);
			}
		}
		output_eq(s);

		map<string, int> c = {};
		map<string, int> last = {};
		for (int i = 1; i < LEN-len+1; i++) {
			for (int j = 0; j <= i; j++) {
				if (EQ[i][j]) {
					string subs = s.substr(i, len);

					int _last = -len - 1;
					if (last.find(subs) != last.end()) {
						_last = last[subs];
					}
					if (_last <= j - len) {
						if (c.find(subs) == c.end()) {
							c[subs] = 1;
						} else {
							c[subs] += 1;
						}
						last[subs] = j;
					}
				}
			}
		}

		if (c.size() == 0) break;

		int max_m = 0;
		for (auto p : c) {
			max_m = p.second > max_m ? p.second : max_m;
#ifdef DEBUG
			cerr << p.first << "\t" << p.second << endl;
#endif
		}

		int len_res = LEN - max_m * (len-1) + len;
		min = len_res < min ? len_res : min;

#ifdef DEBUG
		cerr << max_m << " " << len_res << endl;
		cerr << "-----" << endl;
#endif
	}

	cout << min << endl;
}
