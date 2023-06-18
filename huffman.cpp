#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

const char iname[] = "huffman.in";
const char oname[] = "huffman.out";

typedef long long i64;

struct huffman_node {
	i64 fr;
	int l_index, r_index;

	void set(i64 f, int l, int r) {
		fr = f;
		l_index = l, r_index = r;
	}
};

bool operator < (const huffman_node& a, const huffman_node& b) {
	return a.fr < b.fr;
}

vector <huffman_node> Q;	vector <int> lg;	vector <i64> b;

void walk(int i, int length, i64 code) {
	if (Q[i].l_index + Q[i].r_index == -2) {
		lg[i] = length;
		b[i] = code;
	}
	if (Q[i].l_index >= 0)
		walk(Q[i].l_index, length + 1, code * 2);
	if (Q[i].r_index >= 0)
		walk(Q[i].r_index, length + 1, code * 2 + 1);
}

int main(void) {
	int n;

	ifstream in(iname);
	assert(in >> n);
	Q.resize(2 * n);
	for (int i = 0; i < n; ++ i) {
		int fr;
		assert(in >> fr);
		Q[i].set(fr, -1, -1);
	}
	for (int i = 0, j = n, cnt_n = n; cnt_n < 2 * n - 1; ) {
		int h1 = -1, h2 = -1;
		int limit = min(i + 2, n);
		for (int k = i; k < limit; ++ k) {
			if (h1 == -1 || Q[k] < Q[h1])
				h2 = h1, h1 = k;
			else if (h2 == -1 || Q[k] < Q[h2])
				h2 = k;
		}
		limit = min(j + 2, cnt_n);
		for (int k = j; k < limit; ++ k) {
			if (h1 == -1 || Q[k] < Q[h1])
				h2 = h1, h1 = k;
			else if (h2 == -1 || Q[k] < Q[h2])
				h2 = k;
		}
		Q[cnt_n ++].set(Q[h1].fr + Q[h2].fr, h1, h2);
		(h1 < n) ? ++ i : ++ j;
		(h2 < n) ? ++ i : ++ j;
	}
	lg.resize(n);
	b.resize(n);
	walk(2 * n - 2, 0, 0);

	ofstream out(oname);
	i64 res = 0;
	for (int i = n; i < 2 * n - 1; ++ i)
		res += Q[i].fr;
	out << res << "\n";
	for (int i = 0; i < n; ++ i)
		out << lg[i] << " " << b[i] << "\n";
	out.close();
	return 0;
}
