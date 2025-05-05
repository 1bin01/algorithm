const ll inf = 3e18;    // modify this value
struct line {
    ll a, b;
    ll get(ll x){return a * x + b;}
};

struct node {
    int lc, rc;
    ll s, e;
    line ln;
};

vector<node> Tree;
void init(ll s, ll e) {
    Tree.push_back({-1, -1, s, e, {0, -inf}});
}

void upd(ll ix, line v) {
    auto&[lc, rc, s, e, ln] = Tree[ix];
    ll m = (s + e) / 2;

    line lo = ln, hi = v;
    if (lo.get(s) > hi.get(s)) swap(lo, hi);
    if (lo.get(e) <= hi.get(e)) {
        ln = hi;
        return;
    }

    if (lo.get(m) < hi.get(m)) {    // 오른쪽 재귀
        ln = hi;
        if (rc == -1) {
            rc = Tree.size();
            init(m + 1, e);
        }
        upd(Tree[ix].rc, lo);
    }
    else {  // 왼쪽 재귀
        ln = lo;
        if (lc == -1) {
            lc = Tree.size();
            init(s, m);
        }
        upd(Tree[ix].lc, hi);
    }
}

ll Get(ll ix, ll x) {
    if (ix == -1) return -inf;
    auto&[lc, rc, s, e, ln] = Tree[ix];
    ll m = (s + e) / 2;
    if (x <= m) return max(ln.get(x), Get(lc, x));
    else return max(ln.get(x), Get(rc, x));
}

// main 에서 init(mnx, mxx)
