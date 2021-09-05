#include <bits/stdc++.h>

using namespace std;

// BOJ 14177
// 티떱랜드

#define all(v) v.begin(), v.end()
typedef long long ll;
const int NMAX = 4e3 + 5;
ll n, k, u[NMAX][NMAX], psum[NMAX][NMAX], cost[NMAX][NMAX], dp[NMAX][NMAX];

void go(int t, int l, int r, int optl, int optr) {
	if (l > r) return;
	int mid = (l + r) >> 1, pt = -1;

	for (int j = min(optr, mid - 1); j >= optl; j--) {
		ll x = dp[t - 1][j] + cost[j + 1][mid];
		if (pt == -1 || x < dp[t][mid]) {
			dp[t][mid] = x; pt = j;
		}
	}
	go(t, l, mid - 1, optl, pt);
	go(t, mid + 1, r, pt, optr);
	return;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> u[i][j]; psum[i][j] = psum[i][j - 1] + u[i][j];
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			cost[i][j] = cost[i][j - 1] + psum[j][j] - psum[j][i - 1];

	for (int i = 1; i <= n; i++) dp[1][i] = cost[1][i];
	for (int i = 2; i <= k; i++) go(i, i, n, i - 1, n);
	cout << dp[k][n];
	return 0;
}
