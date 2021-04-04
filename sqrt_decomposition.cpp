#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll NMAX = 1e6 + 5, sqrtn = 1e3;
ll n, m, k, a[NMAX], b[sqrtn + 1], op, l, r, ans;

// BOJ 2042 구간 합 구하기
// square root decomposition

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i]; b[i / sqrtn] += a[i];
	}
	m += k;
	while (m--) {
		cin >> op >> l >> r;
		if (op == 1) {
			l--;
			b[l / sqrtn] += r - a[l];  a[l] = r;
		}
		else {
			l--; r--; ans = 0;
			if (l / sqrtn == r / sqrtn)
				for (int i = l; i <= r; i++) ans += a[i];
			else {
				while (l % sqrtn) ans += a[l++];
				while ((r + 1) % sqrtn) ans += a[r--];
				for (int i = l / sqrtn; i <= r / sqrtn; i++) ans += b[i];
			}
			cout << ans << '\n';
		}
	}
	return 0;
}
