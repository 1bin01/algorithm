#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

const int NMAX = 2e4 + 5;
int N, M, a, b, flag, dfsn[NMAX], cnt, fin[NMAX], sz, sccnum[NMAX];
vector<int> adj[NMAX];
vector<vector<int>> scc;

// BOJ 11281 2-SAT -4
// 타잔 알고리즘을 이용한 2-SAT 구현

int Not(int x) {
	if (x <= N) return x + N;
	return x - N;
}

stack<int> st;
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
		scc.emplace_back(cur); sz++;
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> M;
	while (M--) {
		cin >> a >> b;
		if (a < 0) a = -a + N;
		if (b < 0) b = -b + N;
		adj[Not(a)].emplace_back(b);
		adj[Not(b)].emplace_back(a);
	}

	for (int i = 1; i <= 2 * N; i++)
		if (!dfsn[i]) dfs(i);
	flag = 1;
	for (int i = 1; i <= N; i++)
		if (sccnum[i] == sccnum[i + N]) flag = 0;

	cout << flag << '\n';
	if (!flag) return 0;
	for (int i = 1; i <= N; i++) cout << (sccnum[i] < sccnum[Not(i)]) << ' ';
	return 0;
}
