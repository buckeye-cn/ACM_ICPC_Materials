#include <iostream>
#include <string>

using namespace std;

const uint8_t Forward = 1;
const uint8_t Left = 2;
const uint8_t Right = 3;
const string inss[] = { "E", "Forward", "Left", "Right" };

inline uint8_t next_ins(uint8_t i) {
	return (i == 3) ? 1 : i+1;
}

inline void run(int& cur_x, int& cur_y, int& del_x, int& del_y, uint8_t ins) {
	if (ins == Forward) {
		cur_x += del_x;
		cur_y += del_y;
	} else if (ins == Left) {
		if      (del_x == 0 && del_y == 1) { del_x = -1; del_y =  0; }
		else if (del_x == 1 && del_y == 0) { del_x =  0; del_y =  1; }
		else if (del_x == 0 && del_y ==-1) { del_x =  1; del_y =  0; }
		else if (del_x ==-1 && del_y == 0) { del_x =  0; del_y = -1; }
		else { cerr << "ERR" << endl; }
	} else {
		if      (del_x == 0 && del_y == 1) { del_x =  1; del_y =  0; }
		else if (del_x == 1 && del_y == 0) { del_x =  0; del_y = -1; }
		else if (del_x == 0 && del_y ==-1) { del_x = -1; del_y =  0; }
		else if (del_x ==-1 && del_y == 0) { del_x =  0; del_y =  1; }
		else { cerr << "ERR" << endl; }
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.precision(10);

	int des_x, des_y, n;
	cin >> des_x >> des_y >> n;

	uint8_t step[52] = {};
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		if (s == "Forward")   step[i] = Forward;
		else if (s == "Left") step[i] = Left;
		else                  step[i] = Right;
	}

	int cur_x = 0, cur_y = 0, del_x = 0, del_y = 1;
	for (int i = 0; i < n; i++) {
		uint8_t ins = step[i];

		uint8_t _ins = ins;
		for (int _i = 0; _i < 2; _i++) {
			_ins = next_ins(_ins);
			int _cur_x = cur_x, _cur_y = cur_y, _del_x = del_x, _del_y = del_y;
			run(_cur_x, _cur_y, _del_x, _del_y, _ins);
			for (int j = i+1; j < n; j++) {
				run(_cur_x, _cur_y, _del_x, _del_y, step[j]);
			}
			if (_cur_x == des_x && _cur_y == des_y) {
				cout << i+1 << " " << inss[_ins] << endl;
				return 0;
			}
		}

		run(cur_x, cur_y, del_x, del_y, ins);
	}
}
