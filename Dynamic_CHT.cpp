#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
const ll NMAX = 1e5 + 5, inf = 1e18;
ll n, d[NMAX], p[NMAX], s[NMAX], dp[NMAX];


// BOJ 17526 Star Trek
// LiChao Tree(최솟값 기준)

struct line {
	ll a, b;
	ll get(ll x) { return a * x + b; }
};

struct node {
	ll lc, rc, s, e;
	line ln;
};

vector<node >Tree;
void init(ll s, ll e) {
	Tree.push_back({ -1, -1, s, e, {0, inf} });
	return;
}

void update(ll idx, line v) {
	ll s = Tree[idx].s, e = Tree[idx].e;
	ll m = (s + e) / 2;

	line lw = Tree[idx].ln, h = v;
	if (lw.get(s) > h.get(s)) swap(lw, h);

	if (lw.get(e) <= h.get(e)) {
		Tree[idx].ln = lw; return;
	}

	if (lw.get(m) < h.get(m)) {
		Tree[idx].ln = lw;
		if (Tree[idx].rc == -1) {
			Tree[idx].rc = Tree.size();
			init(m + 1, e);
		}
		update(Tree[idx].rc, h);
	}
	else {
		Tree[idx].ln = h;
		if (Tree[idx].lc == -1) {
			Tree[idx].lc = Tree.size();
			init(s, m);
		}
		update(Tree[idx].lc, lw);
	}
	return;
}

ll sol(ll idx, ll x) {
	if (idx == -1) return inf;
	ll m = (Tree[idx].s + Tree[idx].e) / 2;
	if (x <= m) return min(Tree[idx].ln.get(x), sol(Tree[idx].lc, x));
	else return min(Tree[idx].ln.get(x), sol(Tree[idx].rc, x));
}

/*
int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 2; i <= n; i++) {
		cin >> d[i]; d[i] += d[i - 1];
	}
	for (int i = 1; i < n; i++) cin >> p[i] >> s[i];
	init(0, 2e8);
	for (int i = 1; i <= n; i++) {
		if (i > 1) dp[i] = sol(0, d[i]);
		update(0, { s[i], dp[i] + p[i] - s[i] * d[i] });
	}
	cout << dp[n];
	return 0;
}*/
