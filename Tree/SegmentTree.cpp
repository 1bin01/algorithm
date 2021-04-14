#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

// BOJ 12837 가계부
// 세그먼트 트리 기본 구현

ll N, Q, base = 1, a, b, c;
vector<ll> Tree;

void update(ll idx, ll v) {         // 추가 or (변경)
	idx += base - 1;
	while (idx) {
		Tree[idx] += v; 
		idx /= 2;
	}
	return;
}

ll Sum(ll l, ll r) {
	ll ret = 0;
	l += base - 1; r += base - 1;
	while (l <= r) {
		if (l % 2) ret += Tree[l++];
		if (!(r % 2)) ret += Tree[r--];
		l /= 2; r /= 2;
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> N >> Q;
	while (base < N) base *= 2;
	Tree.resize(base * 2);

	while (Q--) {
		cin >> a >> b >> c;
		if (a == 1) update(b, c);
		else cout << Sum(b, c) << '\n';
	}
	return 0;
}
