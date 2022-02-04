namespace pst {
	struct node {
		int v;
		node* l, * r;
	} nd[NMAX * 5];
	node*root[NMAX];
	int t = 0;

	node* new_node(int x) {
		nd[++t] = { x, NULL, NULL };
		return &nd[t];
	}
	node* init(int l, int r) {
		node* cur = new_node(0);
		if (l == r) return cur;
		int m = l + r >> 1;
		cur->l = init(l, m); 
		cur->r = init(m + 1, r);
		return cur;
	}
	node* update(node* prev, int i, int l, int r, int v) {
		node* cur = new_node(prev->v + v);
		if (l == r) return cur;
		int m = l + r >> 1;
		if (i <= m) {
			cur->l = update(prev->l, i, l, m, v);
			cur->r = prev->r;
		}
		else {
			cur->l = prev->l;
			cur->r = update(prev->r, i, m + 1, r, v);
		}
		return cur;
	}
	int query(node* now, int nl, int nr, int l, int r) {
		if (nl > r || nr < l) return 0;
		if (l <= nl && nr <= r) return now->v;
		int m = nl + nr >> 1;
		return query(now->l, nl, m, l, r) + query(now->r, m + 1, nr, l, r);
	}
}

pst::root[0] = pst::init(0, 100000);
for (int i = 0; i <= 100000; i++) {
	if (i) pst::root[i] = pst::root[i - 1];
	for (int x : arr[i])
	{
		pst::root[i] = pst::update(pst::root[i], x, 0, 100000, 1);
	}
}
