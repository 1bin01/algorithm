struct edge{
    int to, cap, rev, cost;
};
vector<edge> adj[NMAX];

void add_edge(int u, int v, int c, int cost){
    adj[u].push_back({v, c, (int) adj[v].size(), cost});
    adj[v].push_back({u, 0, (int) adj[u].size() - 1, -cost});
    return;
}

int dist[NMAX], p[NMAX], pe[NMAX];
bool inQ[NMAX];
bool spfa(int s, int t){
    fill(dist, dist + NMAX, inf);
    memset(inQ, 0, sizeof(inQ));
    
    queue<int> q;
    q.emplace(s); dist[s] = 0; inQ[s] = 1;
    while(q.size()){
        int x = q.front(); q.pop();
        inQ[x] = 0;
        
        for(int i = 0; i < adj[x].size(); i++){
            auto& e = adj[x][i];
            if(e.cap && dist[x] + e.cost < dist[e.to]){
                dist[e.to] = dist[x] + e.cost;
                p[e.to] = x; pe[e.to] = i;
                if(!inQ[e.to]){
                    inQ[e.to] = 1;
                    q.emplace(e.to);
                }
            }
        }
            
    }
    return dist[t] != inf;
}

int mcmf(int s, int t){
    int ret = 0, flow, rev;
    while(spfa(s, t)){
        flow = inf;
        for(int i = t; i != s; i = p[i])
            flow = min(flow, adj[p[i]][pe[i]].cap);
        ret += flow * dist[t];
        for(int i = t; i != s; i = p[i]){
            rev = adj[p[i]][pe[i]].rev;
            adj[p[i]][pe[i]].cap -= flow;
            adj[i][rev].cap += flow;
        }
    }
    return ret;
}
