#include <bits/stdc++.h>

using namespace std;

#define all(v) v.begin(), v.end()
typedef long long ll;
const int B = 1<<19;
int sz[B], p[B], d[B], top[B], in[B], out[B], t;
ll seg[B * 2];
vector<int> adj[B];

void dfs(int x, int par) {
    sz[x] = 1;
    for (auto&nx : adj[x]) {
        if (nx == par) continue;
        p[nx] = x; d[nx] = d[x] + 1;
        dfs(nx, x);
        if (sz[nx] > sz[adj[x][0]]) swap(nx, adj[x][0]);
    }
}

// main : p[1] = top[1] = 1
void dfs2(int x, int par) {
    in[x] = ++t;
    for (auto& nx : adj[x]) {
        if (nx == par) continue;
        top[nx] = nx == adj[x][0] ? top[x] : nx;
        dfs2(nx, x);
    }
    out[x] = t;
}

// seg에서 수정해 사용
void update(int l, int r) {
    return;
}

ll query(int l, int r) {
    return 1;
}

int LCA(int a, int b) {
    while (top[a] != top[b]) {
        if (d[a] < d[b]) swap(a, b);
        a = p[top[a]];
    }
    if (d[a] > d[b]) swap(a, b);
    return a;
}

void upd(int a, int b) {
    while (top[a] != top[b]) {
        if (d[top[a]] < d[top[b]]) swap(a, b);
        update(in[top[a]], in[a]);
        a = p[top[a]];
    }
    // if (a == b) return; // 간선일 경우만
    if (d[a] > d[b]) swap(a, b);
    update(in[a], in[b]);   // 간선 : in[a] + 1
}

// 합 구하기
ll qry(int a, int b) {
    ll ret = 0;
    while (top[a] != top[b]) {
        if (d[top[a]] < d[top[b]]) swap(a, b);
        ret += query(in[top[a]], in[a]);
        a = p[top[a]];
    }
    // if (a == b) return ret; // 간선일 경우만
    if (d[a] > d[b]) swap(a, b);
    ret += query(in[a], in[b]); //  간선 : in[a] + 1
    return ret;
}
