// 기울기 단조 감소, x값 단조 증가
// 최솟값 구하기 O(n)
// 기울기가 같은 경우 조심!

ll m[NMAX], p[NMAX];
int sz, ii;

long double cross(int a, int b) { return (long double) (p[b] - p[a]) / (m[a] - m[b]); }

void insert(ll mm, ll pp) {
	m[sz] = mm;
	p[sz] = pp;

	while (sz > 1 && cross(sz - 2, sz - 1) >= cross(sz - 1, sz)) {
		m[sz - 1] = m[sz];
		p[sz - 1] = p[sz];
		if (--sz == ii) ii--;
	}
	sz++;
	return;
}

ll go(ll x) {
	while (ii + 1 < sz && cross(ii, ii + 1) <= x) ii++;
	return m[ii] * x + p[ii];
}
