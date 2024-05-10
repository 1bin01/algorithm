// time complexity : O(min(fE, V^2E))
// edge의 capacity가 0 또는 1이라면(unit capacit) : O(V^(2/3)*E, E^(3/2))

struct edge {
	int to, cap, rev;
};
int lv[NMAX], w[NMAX];
vector<edge> adj[NMAX];

void add_edge(int u, int v, int c) {
	adj[u].push_back({ v, c, (int)adj[v].size() });
	adj[v].push_back({ u, 0, (int)adj[u].size() - 1 });
	return;
}

bool bfs(int s, int t) {
	memset(lv, 0, sizeof(lv));
	memset(w, 0, sizeof(w));
	queue<int> q;
	q.emplace(s); lv[s] = 1;
	while (q.size()) {
		int now = q.front();  q.pop();
		for (auto& e : adj[now]) {
			if (e.cap > 0 && !lv[e.to]) {
				lv[e.to] = lv[now] + 1;
				q.emplace(e.to);
			}
		}
	}
	return lv[t];
}

int dfs(int x, int t, int f) {
	if (x == t) return f;
	for (int& i = w[x]; i < adj[x].size(); i++) {
		auto e = adj[x][i];
		if (e.cap > 0 && lv[e.to] == lv[now] + 1) {
			int flow = dfs(e.to, t, min(f, e.cap));
			if (flow) {
				adj[x][i].cap -= flow;
				adj[e.to][e.rev].cap += flow;
				return flow;
			}
		}
	}
	return 0;
}

int dinic(int s, int t) {
	int ret = 0, f;
	while (bfs(s, t)) {
		while (f = dfs(s, t, 1e9)) ret += f;
	}
	return ret;
}
