const int NMAX = 1e5 + 5;
const int b = 350;
int n, a[NMAX], cnt[NMAX], Q, ret, ans[NMAX];

struct query {
	int i, l, r;
	bool operator <(const query& x) const {
		if (l / b == x.l / b) {
			return (l / b & 1) ? r > x.r : r < x.r;
		}
		return l / b < x.l / b;
	}
} q[NMAX];

void f(int c, int ad) {
	if (ad) {
		if (cnt[c]++ == 0) ret++;
	}
	else {
		if (cnt[c]-- == 1) ret--;
	}
	return;
}

for (int i = 0; i < Q; i++) {
		cin >> q[i].l >> q[i].r;
		q[i].i = i;
	}
	sort(q, q + Q);
	int l = 1, r = 0;
	for (int i = 0; i < Q; i++) {
		while (l > q[i].l) f(a[--l], 1);
		while (r < q[i].r) f(a[++r], 1);
		while (l < q[i].l) f(a[l++], 0);
		while (r > q[i].r) f(a[r--], 0);
		ans[q[i].i] = ret;
	}
  for (int i = 0; i < Q; i++) cout << ans[i] << '\n';
