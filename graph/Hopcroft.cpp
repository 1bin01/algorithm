// time complexity : O(EV^(0.5))

const int NMAX = 1005;
int lv[NMAX], L[NMAX], R[NMAX], vis[NMAX];
vector<int> adj[NMAX];

bool bfs(int n) {
    queue<int> q;
    bool ok = 0;
    memset(lv, 0, sizeof(lv));
    for (int i = 1; i <= n; i++)
        if (!L[i]) q.emplace(i), lv[i] = 1;

    while (q.size()) {
        int x = q.front(); q.pop();
        for (auto& r : adj[x]) {
            if (!R[r]) ok = 1;
            else if (!lv[R[r]]) {
                lv[R[r]] = lv[x] + 1;
                q.emplace(R[r]);
            }
        }
    }
    return ok;
}

bool dfs(int x) {
    if (vis[x]) return 0;
    vis[x] = 1;
    for (int& r : adj[x])
        if (!R[r] || lv[R[r]] == lv[x] + 1 && dfs(R[r])) {
            L[x] = r;
            R[r] = x;
            return 1;
        }
    return 0;
}

int hop(int n) {
    int ret = 0;
    memset(L, 0, sizeof(L));
    memset(R, 0, sizeof(R));
    while (bfs(n)) {
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++)
            if (!L[i] && dfs(i)) ret++;
    }
    return ret;
}
