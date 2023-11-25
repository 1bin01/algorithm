// lazy segment tree
// 구간합 기준 구현

const int b = 1 << 18;
ll seg[b * 2], lazy[b * 2];

void upd_lazy(int ix, int l, int r){
    if(!lazy[ix]) return;
    seg[ix] += lazy[ix];
    if(l != r){
        lazy[ix * 2] += lazy[ix];
        lazy[ix * 2 + 1] += lazy[ix];
    }
    lazy[ix] = 0;
    return;
}

void upd(int ix, int nl, int nr, int l, int r, ll v){
    upd_lazy(ix, nl, nr);
    if(nl > r || nr < l) return;
    if(nl >= l && nr <= r){
        lazy[ix] += v;
        upd_lazy(ix, nl, nr);
        return;
    }
    int m = (nl + nr) / 2;
    upd(ix * 2, nl, m, l, r, v);
    upd(ix * 2 + 1, m + 1, nr, l, r, v);
    // modify here
    seg[ix] = seg[ix * 2] + seg[ix * 2 + 1];
    return;
}

ll qry(int ix, int nl, int nr, int l, int r){
    upd_lazy(ix, nl, nr);
    // 더미값 return
    if(nl > r || nr < l) return 0;
    if(nl >= l && nr <= r) return seg[ix];
    int m = (nl + nr) / 2;
    // modify here
    return qry(ix * 2, nl, m, l, r) + qry(ix * 2 + 1, m + 1, nr, l, r);
}
