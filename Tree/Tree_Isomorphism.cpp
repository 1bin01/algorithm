int W[NMAX];
vector<int> adj[NMAX], cent;
// centroid 찾기 (1개 또는 2개)
void get_cent(int now, int bef) {
	int f = 1;
	W[now] = 1;
	for (int nx : adj[now]) {
		if (nx == bef) continue;
		get_cent(nx, now);
		W[now] += W[nx];
		if (W[nx] > n / 2) {
			f = 0; break;
		}
	}
	if (f && n - W[now] <= n / 2) cent.emplace_back(now);
	return;
}

// centroid가 두 2개인 경우 새로운 centroid점을 만들어줌
if (cent.size() == 2) {
	a = cent[0]; b = cent[1];
	adj[a].erase(find(all(adj[a]), b));
	adj[b].erase(find(all(adj[b]), a));
	adj[n + 1].emplace_back(a);
	adj[n + 1].emplace_back(b);
	cent[0] = n + 1;
}

// 트리 해싱
// long long으로 해싱 ("10" base) 또는 map<vector<int>, int> 을 이용
ll dfs(int now, int bef) {
	vector<pair<ll, ll>> v;
	ll ret = 1, x;
	W[now] = 2;
	for (int nx : adj[now]) {
		if (nx == bef) continue;
		x = dfs(nx, now);
		v.emplace_back(x, W[nx]);
		W[now] += W[nx];
	}
	sort(all(v));
	for (auto p : v) {
		ret <<= p.second;
		ret |= p.first;
	}
	ret <<= 1;
	return ret;
}
