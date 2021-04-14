#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
const ll NMAX = 5e4 + 5;
ll N, K, ans, a, b, p[NMAX][19], lv[NMAX], cnt[NMAX], m[NMAX];
vector<ll>  adj[NMAX];

// BOJ 11960 Max Flow
// sparse table을 이용한 O(log(n)) LCA

void dfs(int now, int l) {
	lv[now] = l;
	for (int nxt : adj[now]) {
		if (lv[nxt]) continue;
		p[nxt][0] = now;
		dfs(nxt, l + 1);
	}
	return;
}

void init() {
	for (int j = 1; j < 19; j++)
		for (int i = 1; i <= N; i++)
			p[i][j] = p[p[i][j - 1]][j - 1];
	return;
}

int lca(int a, int b) {
	if (lv[a] < lv[b]) swap(a, b);
	for (int i = 18; i >= 0; i--) {
		if (lv[a] - lv[b] >= (1 << i)) a = p[a][i];
	}
	if (a == b) return a;
	for (int i = 18; i >= 0; i--) {
		if (p[a][i] == p[b][i]) continue;
		a = p[a][i]; b = p[b][i];
	}
	return p[a][0];
}

/*
void dfs2(int now, int bef) {
	for (int nxt : adj[now]) {
		if (nxt == bef) continue;
		dfs2(nxt, now);
	}

	ans = max(ans, cnt[now] - m[now]);
	cnt[now] -= 2 * m[now];
	if (bef != -1) cnt[bef] += cnt[now];
	return;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}

	dfs(1, 1);
	init();
	while (K--) {
		cin >> a >> b;
		cnt[a]++; cnt[b]++;
		m[lca(a, b)]++;
	}
	dfs2(1, -1);
	cout << ans;
	return 0;
}
*/
