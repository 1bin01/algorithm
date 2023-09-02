// P(modular number) should be prime number
const ll M1 = 1e9 + 7, M2 = 1e9 + 9;
// generate base in random
ll n, X1, X2, H[NMAX][2], pw[NMAX][2], 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// 문자열 s[l, r]을 해싱하기
pair<ll, ll> Hash(int l, int r){
	ll y1 = ((H[l][0] - H[r + 1][0] * pw[r - l + 1][0]) % M1 + M1) % M1;
	ll y2 = ((H[l][1] - H[r + 1][1] * pw[r - l + 1][1]) % M2 + M2) % M2;
	return {y1, y2};
}

// 범위 (문자의 개수 + 1, M1 - 1)
static uniform_int_distribution<int> f(300, M1 - 1);
X1 = f(rng); X2 = f(rng);

pw[0][0] = pw[0][1] = 1;
for(int i = 1; i <= n; i++){
	pw[i][0] = pw[i - 1][0] * X1 % M1;
	pw[i][1] = pw[i - 1][1] * X2 % M2;
}

// H[i] = s[i] * X^0 + s[i + 1] * X^1 + ... + s[n - 1] * X^n-1-i
for(int i = n - 1; i >= 0; i--) {
	H[i][0] = (H[i + 1][0] * X1 + s[i]) % M1;
	H[i][1] = (H[i + 1][1] * X2 + s[i]) % M2;
}
