// 기울기, x좌표 단조 증가 O(n)
// 최소값 구하기 upper bound convexhull
// 기울기가 같은 경우 조심

ll m[NMAX], p[NMAX], sz, ii;
int bad(int a, int b, int c){return (p[b] - p[a]) * (m[b] - m[c]) >= (p[c] - p[b]) * (m[a] - m[b]);}
ll get(int i, ll x){return m[i] * x + p[i];}

void insert(ll mm, ll pp) {
	m[sz] = mm;
	p[sz] = pp;
	while(sz > 1 && bad(sz - 2, sz - 1, sz)){
		m[sz - 1] = m[sz];
		p[sz - 1] = p[sz];
		if (--sz == ii) ii--;
	}
	sz++;
	return;
}

ll f(ll x) {
	while (ii + 1 < sz && cross(ii, ii + 1) <= x) ii++;
	return get(ii, x);
}
