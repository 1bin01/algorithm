const int NMAX = 1 << 18; // n * 2
int n, seg[NMAX], lazy[NMAX];

void upd_lazy(int idx, int l, int r){
    if(!lazy[idx]) return;
    seg[idx] += lazy[idx];
    if(l != r){
        lazy[idx * 2] += lazy[idx];
        lazy[idx * 2 + 1] += lazy[idx];
    }
    lazy[idx] = 0;
    return;
}

void upd(int idx, int nl, int nr, int l, int r, int v){
    upd_lazy(idx, nl, nr);
    if(nl > r || nr < l) return;
    if(nl >= l && nr <= r){
        lazy[idx] += v;
        upd_lazy(idx, nl, nr);
        return;
    }
    int m = (nl + nr) / 2;
    upd(idx * 2, nl, m, l, r, v);
    upd(idx * 2 + 1, m + 1, nr, l, r, v);
    seg[idx] = seg[idx * 2] + seg[idx * 2 + 1];
    return;
}

int qry(int idx, int nl, int nr, int l, int r){
    upd_lazy(idx, nl, nr);
    if(nl > r || nr < l) return 0;
    if(nl >= l && nr <= r) return seg[idx];
    int m = (nl + nr) / 2;
    return qry(idx * 2, nl, m, l, r) + qry(idx * 2 + 1, m + 1, nr, l, r);
}
