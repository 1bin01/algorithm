#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

// BOJ 5820 경주
// centroid decomposition

const int NMAX = 2e5 + 5, INF = 1e9;
int N, K, a, b, l;
int sz[NMAX], vis[NMAX], d[1000005];
vector<pair<int, int>> adj[NMAX];
queue<int> Q;

int dfs(int now, int bef) {
	sz[now] = 1;
	for (auto e : adj[now]) {
		int nxt = e.first;
		if (nxt == bef || vis[nxt]) continue;
		sz[now] += dfs(nxt, now);
	}
	return sz[now];
}

int centroid(int now, int bef, int lim) {
	for (auto e : adj[now]) {
		int nxt = e.first;
		if (nxt == bef || vis[nxt]) continue;
		if (sz[nxt] > lim)
			return centroid(nxt, now, lim);
	}
	return now;
}

int go(int now, int bef, int dist, int dpt) {
	int ret = INF;
	if (dist > K) return ret;

	if (d[K - dist] != INF)
		ret = d[K - dist] + dpt;

	for (auto e : adj[now]) {
		int nxt = e.first, c = e.second;
		if (nxt == bef || vis[nxt]) continue;
		ret = min(ret, go(nxt, now, dist + c, dpt + 1));
	}
	return ret;
}

void update(int now, int bef, int dist, int dpt) {
	if (dist > K) return;

	d[dist] = min(d[dist], dpt);
	Q.emplace(dist);

	for (auto e : adj[now]) {
		int nxt = e.first, c = e.second;
		if (nxt == bef || vis[nxt]) continue;
		update(nxt, now, dist + c, dpt + 1);
	}
	return;
}

int sol(int now) {
	int ret = INF;
	int lim = dfs(now, -1) / 2;
	int ct = centroid(now, -1, lim);
	vis[ct] = 1;

	while (Q.size()) {
		d[Q.front()] = INF; Q.pop();
	}
	d[0] = 0;

	for (auto e : adj[ct]) {
		int nxt = e.first, c = e.second;
		if (vis[nxt]) continue;
		ret = min(ret, go(nxt, ct, c, 1));
		update(nxt, ct, c, 1);
	}

	for (auto e : adj[ct]) {
		int nxt = e.first;
		if (vis[nxt]) continue;
		ret = min(ret, sol(nxt));
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b >> l;
		adj[a].emplace_back(b, l);
		adj[b].emplace_back(a, l);
	}

	fill(d, d + 1000005, INF);
	int x = sol(0);
	if (x == INF) cout << -1;
	else cout << x;
	return 0;
}
