int dfsn[NMAX], low[NMAX], vis[NMAX], t, sz;
vector<int> adj[NMAX];

void dfs(int x, int p){
    dfsn[x] = low[x] = ++t;
    int f = 0, c = 0;    // 단절점 구할 때
    
    for(int& nx : adj[x]){
        if(nx == p) continue;
        if(!dfsn[nx]) {
            dfs(nx, x), c++;
            low[x] = min(low[x], low[nx]);
            if(low[nx] >= dfsn[x]) f = 1;
            if(low[nx] > dfsn[x]) ans[1]++; // 단절선
        }
        else low[x] = min(low[x], dfsn[nx]);
    }
    if(f && (p || c > 1)) ans[0]++; // 단절점
    return;
}

int color[NMAX];
void dfs2(int x, int p, int c){
    color[x] = c;
    for(int& nx : adj[x]){
        if(nx == p) continue;
        if(low[nx] > dfsn[x]) dfs2(nx, x, ++sz);
        else dfs2(nx, x, c);
    }
    return;
}
