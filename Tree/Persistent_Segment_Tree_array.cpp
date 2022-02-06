namespace pst {
	struct node {
		int v;
		int l, r;
	} nd[45 * NMAX];
	int root[NMAX];
	int t = 0;
	
	int new_node(int x) {
		nd[++t]={ x, 0, 0 };
		return t;
	}
	int init(int l, int r) {
		int ix = new_node(0);
		if(l == r) return ix;
		int m = l + r >> 1;
		nd[ix].l = init(l, m);
		nd[ix].r = init(m + 1, r);
		return ix;
	}
	int update(int prev, int i, int l, int r, int v) {
		int ix = new_node(nd[prev].v + v);
		if(l == r) return ix;
		int m = l + r >> 1;
		if(i <= m) {
			nd[ix].l = update(nd[prev].l, i, l, m, v);
			nd[ix].r = nd[prev].r;
		}
		else {
			nd[ix].l = nd[prev].l;
			nd[ix].r = update(nd[prev].r, i, m + 1, r, v);
		}
		return ix;
	}
	int query(int ix, int nl, int nr, int l, int r) {
		if(nl > r || nr < l) return 0;
		if(nl >= l && nr <= r) return nd[ix].v;
		int m = nl + nr >> 1;
		return query(nd[ix].l, nl, m, l, r) + query(nd[ix].r, m + 1, nr, l, r);
	}
}

pst::root[0] = pst::init(0, n);
	for(int i = 1; i <= n; i++) {
		pst::root[i] = pst::root[i - 1];
  }
