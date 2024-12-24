// level of tree : O(log(N))

int n, m, op, u, v, color[NMAX];
int W[NMAX], vis[NMAX];
// in Centroid tree
vector<pair<int, int>> Up[NMAX];  // <anc, dist>
multiset<int> S[NMAX];  // for subtree of vertex x

int DFS(int x, int p) {
    W[x] = 1;
    for (int &nx : adj[x])
        if (nx != p && !vis[nx]) W[x] += DFS(nx, x);
    return W[x];
}

// find centroid
int Cent(int x, int p, int k) {
    for (int& nx : adj[x])
        if (nx != p && !vis[nx] && W[nx] > k) return Cent(nx, x, k);
    return x;
}

// Centroid Tree에서 ct의 서브트리 값 갱신
void DFS2(int x, int p, int d, int ct) {
    Up[x].emplace_back(ct, d);
    for (int& nx : adj[x])
        if (nx != p && !vis[nx]) DFS2(nx, x, d + 1, ct);
    return;
}

// Centroid Tree 만들기
void make_tree(int x) {
    int k = DFS(x, -1) / 2;
    int ct = Cent(x, -1, k);    // ct : 현재 centroid 정점
    DFS2(ct, -1, 0, ct);    // ct의 서브트리 update
    vis[ct] = 1;
    for (int& nx : adj[ct])
        if (!vis[nx]) make_tree(nx, ct);
    return;
}
