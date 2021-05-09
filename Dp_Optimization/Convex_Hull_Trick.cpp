#include <iostream>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()
typedef long long ll;
const ll NMAX = 1e5 + 5;
ll n;
ll A[NMAX], B[NMAX], m[NMAX], p[NMAX], sz, ii;

// BOJ 13263 나무 자르기
// CHT (기울기 단조 감소, x 단조 증가) - 최솟값 구하기 O(n)


double cross(ll a, ll b) { return 1.0 * (p[b] - p[a]) / (m[a] - m[b]);  }

void insert(ll mm, ll pp) {
	m[sz] = mm;
	p[sz] = pp;

	while (sz > 1 && cross(sz - 1, sz - 2) >= cross(sz - 1, sz)) {
		m[sz - 1] = m[sz];
		p[sz - 1] = p[sz];
		sz--;
	}
	sz++;
	return;
}

ll go(ll x) {
	while (ii + 1 < sz && cross(ii, ii + 1) <= x) ii++;
	return x * m[ii] + p[ii];
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) cin >> A[i];
	for (int i = 1; i <= n; i++) cin >> B[i];
	insert(B[1], 0);
	for (int i = 2; i <= n; i++) {
		p[i] = go(A[i]);
		insert(B[i], p[i]);
	}
	cout << p[n] << '\n';
	return 0;
}
