//
// <1> HLD로 쪼개기
//

void dfs(int now, int bef) {
	W[now] = 1;
	for (int nx : adj[now]) {
		if (nx == bef) continue;
		par[nx] = now;
		dpt[nx] = dpt[now] + 1;
		dfs(nx, now);
		W[now] += W[nx];
	}
	return;
}

void dfs2(int now, int bef) {
	int c = -1;
	ii[now] = t++;
	for (int nx : adj[now]) {
		if (nx == bef) continue;
		if (c == -1 || W[nx] > W[c]) c = nx;
	}

	if (c != -1) {
		hld[c] = hld[now];
		dfs2(c, now);
	}
	for (int nx : adj[now]) {
		if (nx == bef || nx == c) continue;
		hld[nx] = nx;
		dfs2(nx, now);
	}
	return;
}

void init_hld(int r) {
	hld[r] = par[r] = r;
	dfs(r, -1); dfs2(r, -1);
	while (base < n) base *= 2;
	seg.resize(base * 2);
	lazy.resize(base * 2);
	return;
}


//
// <2> HLD로 쪼갠 상태에서 쿼리 처리
//

void upd(int a, int b) {
	while (hld[a] != hld[b]) {
		if (dpt[hld[a]] < dpt[hld[b]]) swap(a, b);
		update(1, 0, base - 1, ii[hld[a]], ii[a]);
		a = par[hld[a]];
	}
	if (a == b) return; // 간선에 쿼리를 날릴 경우
	if (dpt[a] > dpt[b]) swap(a, b);
	update(1, 0, base - 1, ii[a] + 1, ii[b]);  // 정점에 쿼리를 날릴 경우에는 ii[a]
	return;
}

ll query(int l, int r) {
	ll ret = 0;
	while (hld[a] != hld[b]) {
		if (dpt[hld[a]] < dpt[hld[b]]) swap(a, b);
		ret += Sum(1, 0, base - 1, ii[hld[a]], ii[a]);
		a = par[hld[a]];
	}
	if (a == b) return ret; // 간선에 쿼리를 날릴 경우
	if (dpt[a] > dpt[b]) swap(a, b);
	ret += Sum(1, 0, base - 1, ii[a] + 1, ii[b]);  // 정점에 쿼리를 날릴 경우에는 ii[a]
	return ret;
}
