ll m[NMAX], p[NMAX], sz;
// CHT_이분탐색 (최댓값 기준)

double cross(int a, int b){return 1.0 * (p[b] - p[a]) / (m[a] - m[b]);}

void insert(int mm, int pp){
    m[sz] = mm; p[sz] = pp;
    while(sz > 1 && cross(sz - 2, sz - 1) >= cross(sz - 1, sz)) {
        m[sz - 1] = m[sz];
        p[sz - 1] = p[sz];
        sz--;
    }
    sz++;
    return;
}

ll go(ll x) {
	ll l = 0, r = sz - 1;
	while (l < r) {
		ll m = (l + r) / 2;
		if (cross(m, m + 1) <= x) l = m + 1;
		else r = m;
	}
	return m[l] * x + p[l];
}
