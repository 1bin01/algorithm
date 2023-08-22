// P(modular number) should be prime number
const ll M1 = 1e9 + 7, M2 = 1e9 + 9;
// generate base in random
ll X1, X2;
ll pfx[NMAX][2], pw[NMAX][2];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// 범위 (문자의 개수 + 1, M1 - 1)
static uniform_int_distribution<int> f(300, M1 - 1);
X1 = f(rng); X2 = f(rng);

pw[0][0] = pw[0][1] = 1;
for(int i = 1; i <= n; i++){
	pw[i][0] = pw[i - 1][0] * X1 % M1;
	pw[i][1] = pw[i - 1][1] * X2 % M2;
}

// S = s[1] * X^1 + s[2] * X^2 ... + s[n] * X^n
for(int i = 1; i <= n; i++){
		pfx[i][0] = (pfx[i - 1][0] + s[i - 1] * pw[i][0]) % M1;
		pfx[i][1] = (pfx[i - 1][1] + A[i - 1] * pw[i][1]) % M2;
}

// a[i] * X^i + ... a[j] * X^j 구간 비교하기 -> 최고차항을 X^n으로 맞추고 비교
