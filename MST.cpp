#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

// BOJ 20335 Generators
// 최소 스패닝 트리

typedef long long ll;
struct edge {
	ll u, v, c;
	bool operator < (const edge& x) { return c < x.c; }
};
const ll NMAX = 1e5 + 5;
ll n, m, par[NMAX], a, b, ans;
vector<edge> arr;
ll find(ll x) { return (par[x] == -1) ? x : par[x] = find(par[x]); }

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		arr.push_back({ 0, a, b });
	}
	for (int i = 1; i <= n; i++) {
		cin >> b;
		if (i == n) arr.push_back({ i, 1, b });
		else arr.push_back({ i, i + 1, b });
	}
	
	memset(par, -1, sizeof(par));
	sort(arr.begin(), arr.end());
	for (auto e : arr) {
		a = e.u; b = e.v;
		a = find(a); b = find(b);
		if (a == b) continue;
		if (a > b) swap(a, b);
		par[b] = a; ans += e.c;
	}
	cout << ans;
	return 0;
}
