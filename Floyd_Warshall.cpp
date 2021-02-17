#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int n, m, dist[101][101], a, b, c;

// BOJ 11404 플로이드
// 플로이드 와샬 최단경로 알고리즘
// 음의 사이클이 없을 때 O(N^3)

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	fill(&dist[0][0], &dist[100][101], INF);
	for (int i = 1; i <= n; i++) dist[i][i] = 0;
	while (m--) {
		cin >> a >> b >> c;
		dist[a][b] = min(dist[a][b], c);
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (dist[i][j] == INF) cout << 0 << ' ';
			else cout << dist[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}
