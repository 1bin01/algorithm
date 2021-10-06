void upd_lazy(int idx, int l, int r) {
	if (!lazy[idx]) return;
	seg[idx] += (r - l + 1) * lazy[idx];
	if (l != r) {
		lazy[idx * 2] += lazy[idx];
		lazy[idx * 2 + 1] += lazy[idx];
	}
	lazy[idx] = 0;
	return;
}

void update(int idx, int nl, int nr, int l, int r, ll val) {
	upd_lazy(idx, nl, nr);
	if (nl > r || nr < l) return;
	if (nl >= l && nr <= r) {
		seg[idx] += (nr - nl + 1) * val;
		if (nl != nr) {
			lazy[idx * 2] += val;
			lazy[idx * 2 + 1] += val;
		}
		return;
	}

	int m = (nl + nr) / 2;
	update(idx * 2, nl, m, l, r, val);
	update(idx * 2 + 1, m + 1, nr, l, r, val);
	seg[idx] = seg[idx * 2] + seg[idx * 2 + 1];
	return;
}

ll Sum(int idx, int nl, int nr, int l, int r) {
	upd_lazy(idx, nl, nr);
	if (nl > r || nr < l) return 0;
	if (nl >= l && nr <= r) return seg[idx];
	int m = (nl + nr) / 2;
	return Sum(idx * 2, nl, m, l, r) + Sum(idx * 2 + 1, m + 1, nr, l, r);
}
