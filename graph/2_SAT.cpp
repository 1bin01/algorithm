// 배열 크기는 2배로
// sn값은 리프로 갈수록 더 작음
int n, m;
int dfsn[NMAX], fin[NMAX], sn[NMAX], sz, t;
vector<int> adj[NMAX];
stack<int> st;

int Not(int x) {
	return x <= n ? x + n : x - n;
}

void EQ(int a, int b) {
    OR(a, Not(b));
    OR(Not(a), b);
}

stack<int> st;
int dfs(int x){
    int ret = dfsn[x] = ++t;
    st.emplace(x);
    
    for(int& nx : adj[x]){
        if(!dfsn[nx]) ret = min(ret, dfs(nx));
        else if(!fin[nx]) ret = min(ret, dfsn[nx]);
    }
    
    if(ret == dfsn[x]){
        while(1){
            int y = st.top(); st.pop();
            sn[y] = sz; fin[y] = 1;
            if(y == x) break;
        }
        sz++;
    }
    return ret;
}
