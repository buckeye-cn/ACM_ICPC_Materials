#include <cmath>
#include <iostream>
#include <utility>

using namespace std;

inline bool feq(float a, float b) {
	return abs(a-b) <= 1e-5;
}

inline void sort(unsigned short& a, unsigned short& b) {
	if (a > b) swap(a, b);
}

inline bool between(float x, float a, float b)  {
	if (a < b)
		return a <= x && x <= b;
	else
		return b <= x && x <= a;
}

inline void testcase() {
	float p[7][2] = {};
	float prob;
	for (unsigned short i = 0; i < 7; i++)
		cin >> p[i][0] >> p[i][1];
	cin >> prob;

	unsigned short i1, i2, i3, i4, i5, i6, i7;

	auto _prob = [&]() {
		float _a1 =
			  p[i1][0] * p[i2][1]
			+ p[i2][0] * p[i3][1]
			+ p[i3][0] * p[i4][1]
			+ p[i4][0] * p[i5][1]
			+ p[i5][0] * p[i6][1]
			+ p[i6][0] * p[i7][1]
			+ p[i7][0] * p[i1][1];
		float _a2 =
			  p[i1][1] * p[i2][0]
			+ p[i2][1] * p[i3][0]
			+ p[i3][1] * p[i4][0]
			+ p[i4][1] * p[i5][0]
			+ p[i5][1] * p[i6][0]
			+ p[i6][1] * p[i7][0]
			+ p[i7][1] * p[i1][0];
		float a = _a1 - _a2;
		float _p1 = abs(a) / 2. / 4.;
		return _p1 * _p1 * _p1;
	};

	int8_t _isec_t[7][7][7][7] = {};
	auto isec = [&](unsigned short i1, unsigned short i2, unsigned short i3, unsigned short i4) {
		sort(i1, i2); sort(i3, i4);

		if (_isec_t[i1][i2][i3][i4] == -1) return false;
		if (_isec_t[i1][i2][i3][i4] == 1) return true;

		float x1 = p[i1][0], y1 = p[i1][1];
		float x2 = p[i2][0], y2 = p[i2][1];
		float x3 = p[i3][0], y3 = p[i3][1];
		float x4 = p[i4][0], y4 = p[i4][1];
		float x2x1 = x2 - x1, y1y2 = y1 - y2;
		float x4x3 = x4 - x3, y3y4 = y3 - y4;
		float a1 = y1y2, b1 = x2x1, c1 = x2x1 * y1 + y1y2 * x1;
		float a2 = y3y4, b2 = x4x3, c2 = x4x3 * y3 + y3y4 * x3;
		if ((a1/a2 == b1/b2) && (a1/a2 == c1/c2)) { return false; }

		float x, y;
		if      (a1 == 0.) { y = c1 / b1; x = (c2 - y*b2) / a2; }
		else if (a2 == 0.) { y = c2 / b2; x = (c1 - y*b1) / a1; }
		else if (b1 == 0.) { x = c1 / a1; y = (c2 - x*a2) / b2; }
		else if (b2 == 0.) { x = c2 / a2; y = (c1 - x*a1) / b1; }
		else {
			a2 = a2 / b2 * b1; c2 = c2 / b2 * b1;
			b2 = b2 / b2 * b1;
			x = (c2 - c1) / (a2 - a1);
			y = (c1 - a1*x) / b1;
		}

		bool _isec = between(x, x1, x2) && between(x, x3, x4) && between(y, y1, y2) && between(y, y3, y4);
		_isec_t[i1][i2][i3][i4] = (_isec) ? 1 : -1;
		return _isec;
	};

	auto has_isec = [&]() {
		if (isec(i1, i2, i3, i4)) return true;
		if (isec(i1, i2, i4, i5)) return true;
		if (isec(i1, i2, i5, i6)) return true;
		if (isec(i1, i2, i6, i7)) return true;
		if (isec(i2, i3, i4, i5)) return true;
		if (isec(i2, i3, i5, i6)) return true;
		if (isec(i2, i3, i6, i7)) return true;
		if (isec(i2, i3, i7, i1)) return true;
		if (isec(i3, i4, i5, i6)) return true;
		if (isec(i3, i4, i6, i7)) return true;
		if (isec(i3, i4, i7, i1)) return true;
		if (isec(i4, i5, i6, i7)) return true;
		if (isec(i4, i5, i7, i1)) return true;
		if (isec(i5, i6, i7, i1)) return true;
		return false;
	};

	for (i1 = 0; i1 < 7; i1++) {
	for (i2 = 0; i2 < 7; i2++) { if (i2 == i1) continue;
	for (i3 = 0; i3 < 7; i3++) { if (i3 == i2 || i3 == i1) continue;
	for (i4 = 0; i4 < 7; i4++) { if (i4 == i3 || i4 == i2 || i4 == i1) continue;
	for (i5 = 0; i5 < 7; i5++) { if (i5 == i4 || i5 == i3 || i5 == i2 || i5 == i1) continue;
	for (i6 = 0; i6 < 7; i6++) { if (i6 == i5 || i6 == i4 || i6 == i3 || i6 == i2 || i6 == i1) continue;
	for (i7 = 0; i7 < 7; i7++) { if (i7 == i6 || i7 == i5 || i7 == i4 || i7 == i3 || i7 == i2 || i7 == i1) continue;
		if (feq(_prob(), prob) && !has_isec()) {
			cout << i1+1 << " " << i2+1 << " " << i3+1 << " " << i4+1 << " " << i5+1 << " " << i6+1 << " " << i7+1 << endl;
			return;
		}
	}}}}}}}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.precision(10);

	unsigned int N;
	cin >> N;

	for (unsigned int i = 0; i < N; i++) testcase();
}
