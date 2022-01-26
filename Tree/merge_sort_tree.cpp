const int NMAX = 3e5 + 5;
int n, m, a[NMAX];
vector<int> seg[NMAX];

void make_tree(int idx, int l, int r) {
	if (l == r) {
		seg[idx].emplace_back(a[l]);
		return;
	}
	int m = (l + r) / 2, lc = idx * 2, rc = idx * 2 + 1;
	make_tree(lc, l, m);
	make_tree(rc, m + 1, r);
	vector<int>& lt = seg[lc], &rt = seg[rc], &t = seg[idx];
	seg[idx].resize(lt.size() + rt.size());
	for (int i1 = 0, i2 = 0, i3 = 0; i3 < t.size();) {
		if (i2 == rt.size() || i1 < lt.size() && lt[i1] < rt[i2]) t[i3++] = lt[i1++];
		else t[i3++] = rt[i2++];
	}
	return;
}

int query(int idx, int nl, int nr, int l, int r, int k) {
	if (nl > r || nr < l) return 0;
	if (nl >= l && nr <= r)
		return seg[idx].end() - upper_bound(all(seg[idx]), k);
	int m = (nl + nr) / 2;
	return query(idx * 2, nl, m, l, r, k) + query(idx * 2 + 1, m + 1, nr, l, r, k);
}
