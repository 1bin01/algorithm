// 최댓값 기준
const ll inf = 1e18;
struct line{
    ll a, b;
    ll get(ll x){return a * x + b;}
};
struct CHT {
    // x 범위 : [S, E]
    const ll S = -1e9;
    const ll E = 1e9;
    struct node{
        ll lc, rc, l, r;
        line ln;
    };
    vector<node> Tree;
    int t;  // Tree 노드 개수

    CHT(){Tree.push_back(node(-1, -1, S, E, {0, -inf})); }
    void upd(int ix, line hi){
        ll l = Tree[ix].l, r = Tree[ix].r;
        ll m = (l + r) >> 1;

        line lw = Tree[ix].ln;
        if(lw.get(l) > hi.get(l)) swap(lw, hi);
        if(hi.get(r) >= lw.get(r)) {
            Tree[ix].ln = hi; return;
        }

        if(hi.get(m) >= lw.get(m)){
            Tree[ix].ln = hi;
            if(Tree[ix].rc == -1) {
                Tree[ix].rc = ++t;
                Tree.push_back({-1, -1, m + 1, r, {0, -inf}});  // to modify : 더미 선분
            }
            upd(Tree[ix].rc, lw);
        }
        else{
            Tree[ix].ln = lw;
            if(Tree[ix].lc == -1){
                Tree[ix].lc = ++t;
                Tree.push_back({-1, -1, l, m, {0, -inf}});   // to modify : 더미 선분
            }
            upd(Tree[ix].lc, hi);
        }
    }
    ll qry(int ix, ll x){
        if(ix == -1) return -inf;
        ll m = (Tree[ix].l + Tree[ix].r) >> 1;
        if(x <= m) return max(Tree[ix].ln.get(x), qry(Tree[ix].lc, x));
        else return max(Tree[ix].ln.get(x), qry(Tree[ix].rc, x));
    }

};
