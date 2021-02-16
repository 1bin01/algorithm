#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// BOJ 15561 구간 합 최대? 2
// 구조체 세그트리 응용

typedef long long ll;
const ll INF = 1e18;
struct node {
	ll l, r, m, s;
	node() : l(-INF), r(-INF), m(-INF), s(0){}
	node(ll l, ll r, ll m, ll s): l(l), r(r), m(m), s(s){}
};
ll N, Q, U, V, base = 1, x, a, b, c;
vector<node> Tree;

node merge(node a, node b) {
	return {
		max(a.l, a.s + b.l),
		max(b.r, b.s + a.r),
		max({a.m, b.m, a.r + b.l}),
		a.s + b.s
	};
}

void init() {
	while (base < N) base *= 2;
	Tree.resize(base * 2);

	for (int i = 0; i < N; i++) {
		cin >> x; x = U * x + V;
		Tree[base + i] = { x, x, x, x };
	}
	for (int i = base - 1; i; i--) Tree[i] = merge(Tree[i * 2], Tree[i * 2 + 1]);
	return;
}

void update(ll idx, ll v) {
	idx += base - 1; v = U * v + V;
	Tree[idx] = { v, v, v, v }; idx /= 2;
	while (idx) {
		Tree[idx] = merge(Tree[idx * 2], Tree[idx * 2 + 1]);
		idx /= 2;
	}
	return;
}

node sol(ll idx, ll nl, ll nr, ll l, ll r) {
	if (nl > r || nr < l) return { -INF, -INF, -INF, 0 };
	if (nl >= l && nr <= r) return Tree[idx];
	ll m = (nl + nr) / 2;
	return merge(sol(idx * 2, nl, m, l, r), sol(idx * 2 + 1, m + 1, nr, l, r));
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> N >> Q >> U >> V;
	init();

	while (Q--) {
		cin >> c >> a >> b;
		if (c == 1)
			update(a, b);
		else
			cout << sol(1, 0, base - 1, a - 1, b - 1).m - V << '\n';
	}
	return 0;
}
