#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
ll N, a, b, Max, n, sz, p;
vector<pair<ll, ll>> tmp, arr;
vector<ll> dp, A;

// BOJ 6171 땅따먹기
// CHT (단조 증가할 때)  - 최솟값 기준

double cross(ll a, ll b) { return ((double)(dp[b] - dp[a])) / (A[a] - A[b]); }

void insert(ll a, ll b) {
	A[sz] = a; dp[sz] = b;

	while (sz > 1 && cross(sz - 2, sz - 1) >= cross(sz - 1, sz)) {
		A[sz - 1] = A[sz];
		dp[sz - 1] = dp[sz];
		sz--;
	}
	sz++;
	return;
}

ll sol(ll x) {
	while (p + 1 < sz && cross(p, p + 1) <= x) p++;
	return A[p] * x + dp[p];
}

/*
int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		tmp.emplace_back(-a, -b);
	}
	sort(tmp.begin(), tmp.end());
	Max = -1;
	for (int i = 0; i < N; i++) {
		a = -tmp[i].first; b = -tmp[i].second;
		if (b <= Max) continue;
		Max = max(Max, b);
		arr.emplace_back(a, b);
	}

	n = arr.size();
	dp.resize(n + 1); A.resize(n + 1);

	for (int i = 1; i <= n; i++) {
		a = arr[i - 1].first; b = arr[i - 1].second;
		insert(a, dp[i - 1]);
		dp[i] = sol(b);
	}
	cout << dp[n] << '\n';
	return	 0;
}
*/
