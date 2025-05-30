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
		int x = q.front();  q.pop();
		for (auto& e : adj[x]) {
			if (e.cap && !lv[e.to]) {
				lv[e.to] = lv[x] + 1;
				q.emplace(e.to);
			}
		}
	}
	return lv[t];
}

int dfs(int x, int t, int f) {
	if (x == t) return f;
	for (int& i = w[x]; i < adj[x].size(); i++) {
		auto& e = adj[x][i];
		if (e.cap && lv[e.to] == lv[x] + 1) {
			int flow = dfs(e.to, t, min(f, e.cap));
			if (flow) {
				e.cap -= flow;
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

// min-cut에서 sink에 속하는 원소 구하기
int vis[NMAX];
void dfs2(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto&[nx, cap, rev] : adj[x])
		if(cap > eps) dfs2(nx);
	return;
}

/*
LR flow 구현 시
1. edge (u, v) 용량이 [l, r] 이면, cap(u->T') = l, cap(S'->v) = l, cap(u->v) = r-l
2. cap(T->S) 무한 용량 간선 추가
3. S'->T' flow가 sum(l)이면 flow가 존재.
4. (T->S) 간선(역간선 포함!) 지우고 S->T flow를 흘림
5. 3과 4에서 흘린 flow의 합이 max-flow
max flow는 
*/
