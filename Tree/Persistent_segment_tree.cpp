#include <bits/stdc++.h>

using namespace std;

// boj 11012 Egg
// 퍼시스턴트 세그먼트 트리 - 동적할당 + 포인터 구현

#define all(v) v.begin(), v.end()
typedef long long ll;
const int NMAX = 1e5 + 5;

namespace pst {
	struct node {
		node *l, *r;
		int v;
		node(node* l = NULL, node* r = NULL, int v = 0) : l(l), r(r), v(v){}
	};
	node* init(int s, int e) {
		if (s == e) return new node();
		int m = s + e >> 1;
		return new node(init(s, m), init(m + 1, e));
	}
	node* update(node* prev, int s, int e, int i, int val) {
		if (s == e) return new node(NULL, NULL, prev->v + val);
		int m = s + e >> 1;
		node* ret;
		if (i <= m)
			ret = new node(update(prev->l, s, m, i, val), prev->r);
		else
			ret = new node(prev->l, update(prev->r, m + 1, e, i, val));
		ret->v = ret->l->v + ret->r->v;
		return ret;
	}
	int query(node* now, int s, int e, int l, int r) {
		if (s > r || e < l) return 0;
		if (l <= s && e <= r) return now->v;
		int m = s + e >> 1;
		return query(now->l, s, m, l, r) + query(now->r, m + 1, e, l, r);
	}
}
int tc, n, m, x, xx, y, yy, a, b;
vector<int> arr[NMAX];

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> tc;
	while (tc--) {
		vector<pst::node*> root(NMAX);

		ll ans = 0;
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			arr[y].emplace_back(x);
		}
		
		root[0] = pst::init(0, 100000);
		for (int i = 0; i <= 100000; i++) {
			if (i) root[i] = root[i - 1];
			for (int x : arr[i])
			{
				root[i] = pst::update(root[i], 0, 100000, x, 1);
			}
		}
		while (m--) {
			cin >> x >> xx >> y >> yy;
			a = pst::query(root[yy], 0, 100000, x, xx);
			if (y) b = pst::query(root[y - 1], 0, 100000, x, xx);
			else b = 0;
			ans += a - b;
		}
		cout << ans << '\n';
		for (int i = 0; i <= 100000; i++) arr[i].clear();
	}
	return 0;
}
