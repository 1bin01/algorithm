// Chu–Liu Edmonds' algorithm 
// Directed MST (ElogE)
typedef long long ll;
const int NMAX = 2e5 + 5;
struct edge{
    int u, v;
    ll c;
    bool operator <(const edge& t) const{return c > t.c;}
};
int U[NMAX * 2], P[NMAX * 2], par[NMAX * 2];
int find(int x){return par[x] == -1 ? x : par[x] = find(par[x]);}
ll sum[NMAX * 2];

// 0-based, 각 정점의 부모를 배열로 반환
// 모든 정점이 루트에서 도달가능한 경우
vector<int> DMST(int n, int r, const vector<edge> & E){
    memset(U, -1, sizeof(U));
    memset(P, -1, sizeof(P));
    memset(par, -1, sizeof(par));
    edge par_edge[2 * n];
    vector<int> grp[2 * n];

    priority_queue<edge> Q[2 * n];
    for(auto& e : E) Q[e.v].emplace(e);
    for(int i = 0; i < n; i++) Q[(i + 1) % n].push({i, (i + 1) % n, (ll)1e18});
    
    int cur = 0, t = n;
    while(Q[cur].size()){
        auto e = Q[cur].top(); e.c += sum[cur];
        Q[cur].pop();
        int bef = find(e.u);
        if(cur == bef) continue;
        U[cur] = bef;
        par_edge[cur] = e;

        if(U[bef] == -1) cur = bef;
        else{
            // make new node t
            int x = bef;
            do{
                sum[x] -= par_edge[x].c;
                // merge edges with small to large
                if(Q[x].size() > Q[t].size()) swap(Q[x], Q[t]), swap(sum[x], sum[t]);
                while(Q[x].size()){
                    auto tmp = Q[x].top(); tmp.c += sum[x];
                    Q[x].pop();
                    tmp.c -= sum[t];
                    Q[t].emplace(tmp);
                }
                grp[t].emplace_back(x);
                x = find(U[x]);
            } while(x != bef);
            for(auto x : grp[t]) par[x] = t, P[x] = t;
            cur = t++;
        }
    }

    vector<int> res(n, -1);
    queue<int> q; q.emplace(r);
    while(q.size()){
        int x = q.front(); q.pop();
        while(P[x] != -1){
            for(auto&y : grp[P[x]]){
                if(y == x) continue;
                res[par_edge[y].v] = par_edge[y].u;
                // v를 루트로하는 서브트리에서 다시 탐색
                q.emplace(par_edge[y].v);
                P[y] = -1;
            }
            x = P[x];
        }
    }
    res[r] = r;
    return res;
}
