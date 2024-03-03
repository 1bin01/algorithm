onst int NMAX = 1e5 + 5;
// SZ 크기 조절해주기
const int SZ = 20 * NMAX;
int rt[SZ], lc[SZ], rc[SZ], t;
ll val[SZ];

int init(int l, int r) {
	int ix = ++t;
	if(l == r) return ix;
	int m = (l + r) >> 1;
	lc[ix] = init(l, m);
	rc[ix] = init(m + 1, r);
	return ix;
}

int upd(int prv, int i, int l, int r, ll v){
	int ix = ++t;
	val[ix] = val[prv] + v;
	if(l == r) return ix;

	int m = (l + r) >> 1;
	if(i <= m) {
		lc[ix] = upd(lc[prv], i, l, m, v);
		rc[ix] = rc[prv];
	}
	else {
		lc[ix] = lc[prv];
		rc[ix] = upd(rc[prv], i, m + 1, r, v);
	}
	return ix;
}

// modify this function
// idx 1개 기준 구간합
ll query(int i1, int nl, int nr, int l, int r) {
	if(nl > r || nr < l) return 0;
	if(nl >= l && nr <= r) return val[i1];
	int m = (nl + nr) >> 1;
	return query(lc[i1], nl, m, l, r) + query(rc[i1], m + 1, nr, l, r);
}

// idx 2개 기준 (i2 seg에서 i1 seg를 뺀 상태에서) k번째 원소 구하기
int kth(int i1, int i2, int l, int r, int k) {
	while (l ^ r) {
		ll cnt = val[lc[i2]] - val[lc[i1]];
		int m = (l + r) >> 1;
		if (k <= cnt) r = m, i1 = lc[i1], i2 = lc[i2];
		else l = m + 1, k -= cnt, i1 = rc[i1], i2 = rc[i2];
	}
	return l;
}
