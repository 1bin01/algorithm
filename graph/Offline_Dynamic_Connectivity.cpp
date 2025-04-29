const int B = 1 << 17;
pair<int, int> E[B];
vector<pair<int, int>> seg[B * 2]; // 각 쿼리 구간 [l, r]을 포함하는 간선
int par[B], sz[B], ans[B];
int find(int x){return par[x] == -1 ? x : find(par[x]);}
vector<int> st;

void Union(int a, int b) {  // rank compression
    a = find(a); b = find(b);
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a; sz[a] += sz[b];
    st.emplace_back(b);
}

void Undo() {
    int y = st.back(); st.pop_back();
    sz[par[y]] -= sz[y];
    par[y] = -1;
}

void upd(int ix, int nl, int nr, int l, int r, pair<int, int> v) {
    if (nl > r || nr < l) return;
    if (nl >= l && nr <= r) {
        seg[ix].emplace_back(v);
        return;
    }
    int m = (nl + nr) / 2;
    upd(ix * 2, nl, m, l, r, v);
    upd(ix * 2 + 1, m + 1, nr, l, r, v);
}

void dfs(int ix, int l, int r) {
    int cnt = 0;
    for (auto& [a, b] : seg[ix])
        if (find(a) != find(b)) Union(a, b), cnt++;
    if (l == r) {   // leaf node : answer query
        auto&[a, b] = E[l];
        if (a) ans[l] = find(a) == find(b);  // 하나의 component에 속하는지 확인
    }
    else {
        int m = (l + r) / 2;
        dfs(ix * 2, l, m);
        dfs(ix * 2 + 1, m + 1, r);
    }
    while (cnt--) Undo();
}

map<pair<int, int>, int> S;  // a < b
int n, m, op, a, b;

// <main>
// memset(par, -1, sizeof(par));
// for (int i = 1; i <= n; i++) sz[i] = 1;
// 마지막까지 있는 간선 update
