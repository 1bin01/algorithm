// 배열 크기는 2배로
int n, m;
int dfsn[NMAX], fin[NMAX], sn[NMAX], sz, t;
vector<int> adj[NMAX];
stack<int> st;

int Not(int x) {
	return x <= n ? x + n : x - n;
}

int dfs(int now) {
	int ret = dfsn[now] = ++t;
	st.emplace(now);

	for(int nx : adj[now]) {
		if(!dfsn[nx]) ret = min(ret, dfs(nx));
		else if(!fin[nx]) ret = min(ret, dfsn[nx]);
	}

	if(ret == dfsn[now]) {
		while(1) {
			int x = st.top(); st.pop();
			sn[x] = sz; fin[x]= 1;
			if(x == now) break;
		}
		sz++;
	}
	return ret;
}
