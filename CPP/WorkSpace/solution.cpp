// It's a wonderful life.
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7, M = 2e5 + 7;
int n, m, k, u[M], v[M], f[N<<1], d[N<<1];
struct T {
	int l, r;
	vector<int> e;
} t[N<<2];
stack< pi > s;

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) return;
	build(ls, l, md), build(rs, md + 1, r);
}

void ins(int p, int l, int r, int x) {
	if (t[p].l >= l && t[p].r <= r) return t[p].e.pb(x), void();
	if (l <= md) ins(ls, l, r, x);
	if (r > md) ins(rs, l, r, x);
}

inline int get(int x) {
	while (x ^ f[x]) x = f[x];
	return x;
}

inline void merge(int x, int y) {
	if (x == y) return;
	if (d[x] > d[y]) swap(x, y);
	s.push(mp(x, d[x] == d[y])), f[x] = y, d[y] += d[x] == d[y];
}

void dfs(int p, int l, int r) {
	bool ok = 1;
	ui o = s.size();
	for (ui i = 0; i < t[p].e.size(); i++) {
		int x = t[p].e[i], u = get(::u[x]), v = get(::v[x]);
		if (u == v) {
			for (int j = l; j <= r; j++) prints("No");
			ok = 0;
			break;
		}
		merge(get(::u[x] + N), v), merge(get(::v[x] + N), u);
	}
	if (ok) {
		if (l == r) prints("Yes");
		else dfs(ls, l, md), dfs(rs, md + 1, r);
	}
	while (s.size() > o) d[f[s.top().fi]] -= s.top().se, f[s.top().fi] = s.top().fi, s.pop();
}

int main() {
	rd(n), rd(m), rd(k), build(1, 1, k);
	for (int i = 1, l, r; i <= m; i++) {
		rd(u[i]), rd(v[i]), rd(l), rd(r);
		if (l ^ r) ins(1, l + 1, r, i);
	}
	for (int i = 1; i <= n; i++) f[i] = i, f[i+N] = i + N;
	dfs(1, 1, k);
	return 0;
}