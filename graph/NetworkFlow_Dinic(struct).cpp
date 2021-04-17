#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// BOJ 14955 How Many to Be Happy?
// NetworkFlow - Dinic algorithm with struct

struct Edge {
	int to, cap, flow;
	Edge* reverse;
	Edge(int to, int cap) : to(to), cap(cap), flow(0) {};
	int rest() { return cap - flow; }
	void push(int f) {
		flow += f; reverse->flow -= f;
	}
};

struct edge {
	int u, v, c;
	bool operator < (const edge& x) { return c < x.c; }
};

#define NMAX 110
int n, m, a, b, c, ans;
vector<Edge*> adj[NMAX];
edge arr[510];

void addEdge(int u, int v, int cap) {
	Edge* uv = new Edge(v, cap), * vu = new Edge(u, 0);
	uv->reverse = vu; vu->reverse = uv;
	adj[u].emplace_back(uv);
	adj[v].emplace_back(vu);
	return;
}

int lv[NMAX], now, nxt, idx;
bool bfs(int s, int t) {
	memset(lv, -1, sizeof(lv));
	queue<int> Q; Q.emplace(s); lv[s] = 0;
	while (Q.size()) {
		now = Q.front(); Q.pop();
		for (auto e : adj[now]) {
			nxt = e->to;
			if (lv[nxt] == -1 && e->rest() > 0) {
				lv[nxt] = lv[now] + 1; Q.emplace(nxt);
			}
		}
	}
	return lv[t] != -1;
}

int work[NMAX];
int dfs(int now, int t, int f) {
	if (now == t) return f;
	for (int& i = work[now]; i < adj[now].size(); i++) {
		auto e = adj[now][i]; int nxt = e->to;
		if (lv[nxt] == lv[now] + 1 && e->rest() > 0) {
			int flow = dfs(nxt, t, min(f, e->rest()));
			if (flow) {
				e->push(flow); return flow;
			}
		}
	}
	return 0;
}

const int INF = 1987654321;
int dinic(int s, int t) {
	int totalflow = 0;
	while (bfs(s, t)) {
		memset(work, 0, sizeof(work));
		while (1) {
			int f = dfs(s, t, INF);
			if (!f) break;
			totalflow++;
		}
	}
	return totalflow;
}

void init() {
	for (int now = 1; now <= n; now++)
		for (auto e : adj[now])
			e->flow = 0;
	return;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> arr[i].u >> arr[i].v >> arr[i].c;
	}
	sort(arr, arr + m);
	for (int i = 0; i < m; i++) {
		while (idx < i && arr[idx].c < arr[i].c) {
			a = arr[idx].u; b = arr[idx].v;
			addEdge(a, b, 1);
			addEdge(b, a, 1);
			idx++;
		}
		a = arr[i].u; b = arr[i].v;
		ans += dinic(a, b);
		init();
	}
	cout << ans << '\n';
	return 0;
}
