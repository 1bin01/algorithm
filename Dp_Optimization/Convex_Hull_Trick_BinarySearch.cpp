#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
const ll NMAX = 3e5 + 5;
ll N, arr[NMAX], Sum[NMAX], a[NMAX], b[NMAX], sz, ans, ret;

// BOJ 5254 Balls
// CHT_이분탐색 (최댓값 기준)

double cross(ll x, ll y) { return ((double)b[x] - b[y]) / (a[y] - a[x]); }

void insert(ll aa, ll bb) {
	a[sz] = aa; b[sz] = bb;

	while (sz > 1 && cross(sz - 2, sz - 1) <= (cross(sz - 1, sz))) {
		a[sz - 1] = a[sz];
		b[sz - 1] = b[sz];
		sz--;
	}
	sz++;
	return;
}

ll find(ll x) {
	ll l = 0, r = sz - 1;
	while (l < r) {
		ll m = (l + r) / 2;
		if (cross(m, m + 1) <= x) r = m;
		else l = m + 1;
	}
	return a[l] * x + b[l];
}

void sol() {
	memset(Sum, 0, sizeof(Sum)); sz = 0; ans = -1e18;
	for (int i = 1; i <= N; i++)
		Sum[i] = Sum[i - 1] + arr[i];

	for (int i = 1; i <= N; i++) {
		if (i > 1) {
			ret = find(arr[i]) + arr[i] * i + Sum[N] - Sum[i];
			ans = max(ans, ret);
		}
		insert(-(i - 1), Sum[i - 1]);
	}
	cout << ans << '\n';
	return;
}

/*
int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) cin >> arr[i];
	sol();
	reverse(arr + 1, arr + N + 1);
	sol();
	return 0;
}
*/
