#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

const int NMAX = 1e4 + 5;
int V, E, a, b, dfsn[NMAX], cnt, fin[NMAX], sz, sccnum[NMAX];
vector<int> adj[NMAX];
stack<int> st;
vector<vector<int>> scc;

// BOJ 2150 Strongly Connected Component
// SCC - 타잔 알고리즘

int dfs(int now) {
	dfsn[now] = ++cnt;
	st.emplace(now);

	int ret = dfsn[now];
	for (int nxt : adj[now]) {
		if (!dfsn[nxt]) ret = min(ret, dfs(nxt));
		else if (!fin[nxt]) ret = min(ret, dfsn[nxt]);
	}

	if (ret == dfsn[now]) {
		vector<int> cur;
		while (1) {
			int x = st.top(); st.pop();
			cur.emplace_back(x);
			fin[x] = 1;
			sccnum[x] = sz;
			if (x == now) break;
		}
		//sort(cur.begin(), cur.end());
		scc.emplace_back(cur); sz++;
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> V >> E;
	while (E--) {
		cin >> a >> b;
		adj[a].emplace_back(b);
	}
	for (int i = 1; i <= V; i++) 
		if(!dfsn[i]) dfs(i);

	sort(scc.begin(), scc.end());
	cout << sz << '\n';
	for (int i = 0; i < sz; i++) {
		for (int x : scc[i]) cout << x << ' ';
		cout << -1 << '\n';
	}
	return 0;
}
