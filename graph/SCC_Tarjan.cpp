int n, dfsn[NMAX], fin[NMAX], sn[NMAX], t, sz;
vector<int> adj[NMAX];
vector<vector<int>> scc;
stack<int> st;

int dfs(int x){
    dfsn[x] = ++t;
    st.emplace(x);
    
    int ret = dfsn[x];
    for(int& nx : adj[x]){
        if(!dfsn[nx]) ret = min(ret, dfs(nx));
        else if(!fin[nx]) ret = min(ret, dfsn[nx]);
    }
    
    if(ret == dfsn[x]){
        vector<int> v;
        while(1){
            int y = st.top(); st.pop();
            v.emplace_back(y);
            fin[y] = 1;
            sn[y] = sz;
            if(y == x) break;
        }
        sort(all(v));
        scc.emplace_back(v); sz++;
    }
    return ret;
}

    for(int i =1; i <= n; i++)
        if(!dfsn[i]) dfs(i);
