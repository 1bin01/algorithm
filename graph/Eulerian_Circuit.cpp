// 오일러 회로(양방향 간선 기준)
int w[NMAX], used[MMAX];
vector<pair<int, int>> adj[NMAX];
vector<int> v;
void dfs(int x) {
	for (;w[x] < adj[x].size();) {
		auto&[nx, e] = adj[x][w[x]++];
		if(used[e]) continue;
		used[e] = 1;
		dfs(nx);
	}
	// vector에 역순으로 저장
	v.emplace_back(x);
	return;
}
