#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
ll n, q, qq, base = 1, a, b, c, d;
vector<ll> Tree, lazy;

// BOJ 15967 에바쿰
// lazy세그트리 구간 합 구하기

void update_lazy(ll idx, ll l, ll r) {
	if (!lazy[idx]) return;
	Tree[idx] += (r - l + 1) * lazy[idx];
	if (l != r) {
		lazy[idx * 2] += lazy[idx];
		lazy[idx * 2 + 1] += lazy[idx];
	}
	lazy[idx] = 0;
	return;
}

void update(ll idx, ll nl, ll nr, ll l, ll r, ll v) {
	update_lazy(idx, nl, nr);
	if (nl > r || nr < l) return;
	if (nl >= l && nr <= r) {
		Tree[idx] += (nr - nl + 1) * v;
		if (nl != nr) {
			lazy[idx * 2] += v; lazy[idx * 2 + 1] += v;
		}
		return;
	}
	ll m = (nl + nr) / 2;
	update(idx * 2, nl, m, l, r, v);
	update(idx * 2 + 1, m + 1, nr, l, r, v);
	Tree[idx] = Tree[idx * 2] + Tree[idx * 2 + 1];
	return;
}

ll Sum(ll idx, ll nl, ll nr, ll l, ll r) {
	update_lazy(idx, nl, nr);
	if (nl > r || nr < l) return 0;
	if (nl >= l && nr <= r) return Tree[idx];
	ll m = (nl + nr) / 2;
	return Sum(idx * 2, nl, m, l, r) + Sum(idx * 2 + 1, m + 1, nr, l, r);
}

int main(void) {
	ios::sync_with_stdio(0);
	
	cin >> n >> q >> qq; q += qq;
	while (base < n) base *= 2;
	Tree.resize(base * 2); lazy.resize(base * 2);

	for (int i = 0; i < n; i++) cin >> Tree[base + i];
	for (int i = base - 1; i; i--) Tree[i] = Tree[i * 2] + Tree[i * 2 + 1];

	while (q--) {
		cin >> a >> b >> c; b--; c--;
		if (a == 1) cout << Sum(1, 0, base - 1, b, c) << '\n';
		else {
			cin >> d;
			update(1, 0, base - 1, b, c, d);
		}
	}
	return 0;
}
