#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

// BOJ 11003 최솟값 찾기

int N, L, x;
deque<pair<int, int>> dq;

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		cin >> x;
		while (dq.size() && dq.back().first >= x) dq.pop_back();
		dq.emplace_back(x, i);
		while (i - dq.front().second >= L) dq.pop_front();
		cout << dq.front().first << ' ';
	}
	return 0;
}
