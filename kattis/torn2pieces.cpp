#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int N;
int n_i = 0;
string stations[33] = {};
bool conn[33][33] = {};

inline int get_i_st(string& st) {
	for (int i = 0; i < n_i; i++) {
		if (stations[i] == st) {
			return i;
		}
	}

	stations[n_i] = st;
	n_i++;

	return n_i-1;
}

inline bool arrive(int des, vector<int>& vistied) {
	int o = vistied.back();
	if (o == des) {
		return true;
	}

	for (int i = 0; i < n_i; i++) {
		bool has = false;
		for (int v : vistied)
			if (v == i) {
				has = true;
				break;
			}

		if (!has && conn[o][i]) {
			vistied.push_back(i);
			bool arr = arrive(des, vistied);
			if (arr) {
				return true;
			} else {
				vistied.pop_back();
			}
		}
	}
	return false;
}

int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		string station;
		cin >> station;
		int i_st = get_i_st(station);
		while (cin.peek() != '\n') {
			string s;
			cin >> s;
			int _i_st = get_i_st(s);
			conn[i_st][_i_st] = true;
			conn[_i_st][i_st] = true;
		}
	}

	//{ // debug conn
	//	cout << "  ";
	//	for (int i = 0; i < n_i; i++) {
	//		cout << stations[i] << " ";
	//	}
	//	cout << endl;
	//	for (int i = 0; i < n_i; i++) {
	//		cout << stations[i] << " ";
	//		for (int j = 0; j < n_i; j++) {
	//			cout << conn[i][j] << " ";
	//		}
	//		cout << endl;
	//	}
	//}

	int ori;
	{
		string _ori;
		cin >> _ori;
		ori = get_i_st(_ori);
	}
	int des;
	{
		string _des;
		cin >> _des;
		des = get_i_st(_des);
	}

	vector<int> vistied;
	vistied.push_back(ori);

	bool arr = arrive(des, vistied);

	if (arr) {
		for (unsigned long i = 0; i < vistied.size(); i++) {
			cout << stations[vistied[i]];
			if (i < vistied.size() - 1)
				cout << " ";
			else
				cout << endl;
		}
	} else {
		cout << "no route found" << endl;
	}
}
