const int B = 1<<17;  // base
const ll E = 1<<30;  // range : [0, E]
ll t, n, m, q, p;
struct node {
    int l, r;
    ll v;
    node(){l = r = -1; v = 0;}
} nd[B * 33];

// upd(i, v)
void upd(int ix, int l, int r, int i, ll v) {
    if (l == r) {
        nd[ix].v = v;
        return;
    }
    int m = (l + r) / 2;
    if (i <= m) {
        if (nd[ix].l == -1) nd[ix].l = ++t;
        upd(nd[ix].l, l, m, i, v);
    }
    else {
        if (nd[ix].r == -1) nd[ix].r = ++t;
        upd(nd[ix].r, m + 1, r, i, v);
    }
    ll a = nd[ix].l == -1 ? 0 : nd[nd[ix].l].v;
    ll b = nd[ix].r == -1 ? 0 : nd[nd[ix].r].v;
    // modify : 구간 합
    nd[ix].v = a + b;
    return;
}

ll qry(int ix, int nl, int nr, int l, int r) {
    if (ix == -1) return 0;
    if (nl > r || nr < l) return 0;
    if (nl >= l && nr <= r) return nd[ix].v;
    int m = (nl + nr) / 2;
    // modify : 구간합
    return qry(nd[ix].l, nl, m, l, r) + qry(nd[ix].r, m + 1, nr, l, r);
}
