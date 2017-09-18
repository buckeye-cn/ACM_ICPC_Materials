#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
	int len;
	int bs[5001] = { 0 };
	int accum[5001] = { 0 };

	{
		string str;
		cin >> str;

		len = str.length();

		int n = 0;
		for (int i = 0; i < len; i++) {
			int _bs = (str[i] == '(') ? 1 : -1;
			bs[i + 1] = _bs;
			n += _bs;
			accum[i + 1] = n;
		}
	}

	if (len % 2 == 1) {
		cout << "impossible" << endl;
		return 0;
	}

	int first_neg = len;

	{
		bool valid = true;
		for (int i = 1; i <= len; i++) {
			if (accum[i] < 0) {
				if (i < first_neg) {
					first_neg = i;
				}
				valid = false;
				break;
			}
		}
		if (accum[len] != 0) {
			valid = false;
		}
		if (valid) {
			cout << "possible" << endl;
			return 0;
		}
	}

	int n_to_flip = accum[len];

	int j_min = len;
	for (j_min = len; j_min >= 0; j_min--) {
		if (accum[j_min] < n_to_flip) {
			break;
		}
	}

	for (int i = 0; i < first_neg; i++) {
		int a = accum[i];
		int b = a + n_to_flip / 2;

		int last_k = i;
		for (int j = max(j_min, i + 1); j <= len; j++) {
			if (accum[j] == b) {
				bool fail = false;
				for (int k = last_k; k <= j; k++) {
					if (2 * a - accum[k] < 0) {
						fail = true;
						break;
					}
				}
				if (!fail) {
					cout << "possible" << endl;
					return 0;
				} else {
					break;
				}
			}
		}
	}

	cout << "impossible" << endl;
}
