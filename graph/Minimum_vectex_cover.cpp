// 이분매칭 O(VE)
int v[NMAX], L[NMAX], R[NMAX];
vector<int> adj[NMAX];

int dfs(int x) {
	if (v[x]) return 0;
	v[x] = 1;

	for(int& nx : adj[x]) {
		if (!R[nx] || dfs(R[nx])) {
			R[nx] = x; L[x] = nx;
			return 1;
		}
	}
	return 0;
}

// minium vertex cover 원소 구하기
// X : L의 매칭되지 않은 정점으로부터 도달할 수 있는 L, R의 모든 정점
// L : 1~n , R : n+1 ~ n+m
// C = (L - X) U (R ∩ X)
int X[NMAX * 2], C[NMAX * 2];	
void go(int x) {
	if (X[x]) return;
	X[x] = 1;	
	for (int& nx : adj[x]) {
		X[nx + n] = 1;
		go(R[nx]);
	}
	return;
} 

// 
int main(void){
 for (int i = 1; i <= n; i++) {
		memset(v, 0, sizeof(v));
		if (dfs(i)) ans++;
	}
	for (int i = 1; i <= n; i++)
		if (!L[i]) go(i);	// L의 매칭되지 않은 정점들로부터 탐색

	// mvc 구하기
	for (int i = 1; i <= n; i++) C[i] = !X[i];
	for (int i = n + 1; i <= n + m; i++) C[i] = X[i]; 
}
