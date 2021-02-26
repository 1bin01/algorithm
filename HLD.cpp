#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

// BOJ 2927 남극 탐험
// Heavy-Light 분할 (가중치가 정점에 있는 경우)

struct rmq {
	char c;
	int a, b;
};
const int NMAX = 3e4 + 4;
int N, Q, cnt[NMAX], a, b, pa, pb, p[NMAX];
int base = 1, nn, num[NMAX], idx[NMAX], hld[NMAX], dpt[NMAX], par[NMAX], W[NMAX];
vector<int> adj[NMAX], Tree;
vector<rmq> tmp;
string s;

int find(int x) { return (p[x] == -1) ? x : p[x] = find(p[x]); }

void dfs(int now) {
	W[now] = 1;
	for (int nxt : adj[now]) {
		if (W[nxt]) continue;
		par[nxt] = now;
		dpt[nxt] = dpt[now] + 1;
		dfs(nxt);
		W[now] += W[nxt];
	}
	return;
}

void dfs2(int now) {
	int c = -1;
	num[now] = nn++; idx[num[now]] = now;
	for (int nxt : adj[now]) 
		if (par[nxt] == now && (c == -1 || W[nxt] > W[c])) c = nxt;
	if (c != -1) {
		hld[c] = hld[now];
		dfs2(c);
	}
	for (int nxt : adj[now]) 
		if (par[nxt] == now && nxt != c) {
			hld[nxt] = nxt;
			dfs2(nxt);
		}
	return;
}

void init_hld(int r) {
	hld[r] = par[r] = r;
	dfs(r); dfs2(r);
	return;
}

void init_seg() {
	while (base < N) base *= 2;
	Tree.resize(base * 2);
	for (int i = 1; i <= N; i++) Tree[base + num[i]] = cnt[i];
	for (int i = base - 1; i; i--) Tree[i] = Tree[i * 2] + Tree[i * 2 + 1];
	return;
}

void update(int idx, int v) {
	idx += base;
	Tree[idx] = v; idx /= 2;
	while (idx) {
		Tree[idx] = Tree[idx * 2] + Tree[idx * 2 + 1];
		idx /= 2;
	}
	return;
}

int sol(int l, int r) {
	int ret = 0;
	l += base; r += base;
	while (l <= r) {
		if (l % 2) ret += Tree[l++];
		if (!(r % 2)) ret += Tree[r--];
		l /= 2; r /= 2;
	}
	return ret;
}

int query(int a, int b) {
	int ret = 0;
	while (hld[a] != hld[b]) {
		if (dpt[hld[a]] < dpt[hld[b]]) swap(a, b);
		ret += sol(num[hld[a]], num[a]);
		a = par[hld[a]];
	}
	if (dpt[a] > dpt[b]) swap(a, b);
	ret += sol(num[a], num[b]);
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) cin >> cnt[i];

	memset(p, -1, sizeof(p));
	cin >> Q;
	while (Q--) {
		cin >> s >> a >> b;
		tmp.push_back({ s[0], a, b });
		if (s == "bridge") {
			pa = find(a); pb = find(b);
			if (pa == pb) continue;
			adj[a].emplace_back(b);
			adj[b].emplace_back(a);
			p[pb] = pa;
		}
	}
	for (int i = 1; i <= N; i++)
		if (!W[i]) init_hld(i);
	init_seg();
	
	memset(p, -1, sizeof(p));
	for (auto q : tmp) {
		if (q.c == 'b') {
			pa = find(q.a); pb = find(q.b);
			if (pa != pb) {
				p[pb] = pa;
				cout << "yes\n";
			}
			else cout << "no\n";
		}
		else if (q.c == 'p') update(num[q.a], q.b);
		else {
			pa = find(q.a); pb = find(q.b);
			if (pa != pb) {
				cout << "impossible\n"; continue;
			}
			cout << query(q.a, q.b) << '\n';
		}
	}
	return 0;
}
