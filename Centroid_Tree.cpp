#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define all(v) v.begin(), v.end()
typedef long long ll;

const int NMAX = 1e5 + 5;
int n, m, a, b, op, x, chk[NMAX];
int W[NMAX], vis[NMAX], par[NMAX], dpt[NMAX], sparse[NMAX][18];
vector<int> adj[NMAX];
priority_queue<pair<int, int>> pq[NMAX];

// BOJ 13514 트리와 쿼리 5
// Centroid Tree

int dfs(int now, int bef) {
	W[now] = 1;
	for (int nxt : adj[now]) {
		if (nxt == bef || vis[nxt]) continue;
		W[now] += dfs(nxt, now);
	}
	return W[now];
}

int centroid(int now, int bef, int lm) {
	for (int nxt : adj[now]) {
		if (nxt == bef || vis[nxt]) continue;
		if (W[nxt] > lm)
			return centroid(nxt, now, lm);
	}
	return now;
}

void make_tree(int now, int bef) {					 
	int lm = dfs(now, -1) / 2;
	int ct = centroid(now, -1, lm);
	par[ct] = bef;										// par[1] = 0;
	vis[ct] = 1;

	for (int nxt : adj[ct])
		if (!vis[nxt]) make_tree(nxt, ct);
	return;
}

void dfs2(int now, int bef, int d) {
	dpt[now] = d;
	for (int nxt : adj[now]) {
		if (nxt == bef)continue;
		sparse[nxt][0] = now;
		dfs2(nxt, now, d + 1);
	}
	return;
}

void make_sparse() {
	dfs2(1, -1, 0);
	for (int j = 1; j < 18; j++)
		for (int i = 1; i <= n; i++)
			sparse[i][j] = sparse[sparse[i][j - 1]][j - 1];
	return;
}

int dist(int a, int b) {
	int ret = 0;
	if (dpt[a] < dpt[b]) swap(a, b);
	for (int i = 17; i >= 0; i--) 
		if (dpt[a] - dpt[b] >= (1 << i)) {
			ret += (1 << i);
			a = sparse[a][i];
		}

	if (a == b) return ret;
	for (int i = 17; i >= 0; i--) 
		if (sparse[a][i] != sparse[b][i]) {
			ret += 2 * (1 << i);
			a = sparse[a][i];
			b = sparse[b][i];
		}
	return ret + 2;
}

void update(int x) {
	int xx = x;
	while (xx) {
		while (pq[xx].size() && !chk[pq[xx].top().second]) pq[xx].pop();
		pq[xx].emplace(-dist(x, xx), x);
		xx = par[xx];
	}
	return;
}

int query(int x) {
	int ret = 1e9, xx = x;
	while (xx) {
		while (pq[xx].size() && !chk[pq[xx].top().second]) pq[xx].pop();
		if (pq[xx].size()) ret = min(ret, dist(x, xx) + -pq[xx].top().first);
		xx = par[xx];
	}
	if (ret == 1e9) return -1;
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}

	make_tree(1, 0);
	make_sparse();

	cin >> m;
	while (m--) {
		cin >> op >> x;
		if (op == 1) {
			chk[x] ^= 1;
			if (chk[x]) update(x);
		}
		else cout << query(x) << '\n';
	}
		
	return 0;
}
