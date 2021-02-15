#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;
int N, M, dp[301][1<<18], m;
const int mod = 1e9 + 7;

// BOJ 14700 넴모넴모(Hard)
// 격자판에서의 비트마스크 dp

int sol(int idx, int st) {
	int& ret = dp[idx][st];
	if (ret != -1) return ret;
	if (idx == N * M) return ret = 1;

	if (idx % M) 
		if ((st & 1) && (st & (1 << M - 1)) && (st & (1 << M)))
			return ret = sol(idx + 1, (st << 1) % m);
	ret = sol(idx + 1, ((st << 1) | 1) % m);
	ret += sol(idx + 1, (st << 1) % m); ret %= mod;
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> M;
	if (M > N) swap(N, M);

	m = 1 << M + 1;
	memset(dp, -1, sizeof(dp));
	cout << sol(0, 0);
	return 0;
}
