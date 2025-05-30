const int B = 1 << 18;
namespace pst {
    struct node {
        ll v;
        int l, r;
    } nd[20 * B];
    int root[B];
    int t = 0;

    int new_node(ll x) {
        nd[++t]={ x, 0, 0 };
        return t;
    }
    int init(int l, int r) {
        int ix = new_node(0);
        if(l == r) return ix;
        int m = (l + r) / 2;
        nd[ix].l = init(l, m);
        nd[ix].r = init(m + 1, r);
        return ix;
    }
    int update(int prev, int l, int r, int i, ll v) {
        int ix = new_node(nd[prev].v + v);    // 새로 node를 만들 때 값 주기
        if(l == r) return ix;
        int m = (l + r) / 2;
        if(i <= m) {
            nd[ix].l = update(nd[prev].l, l, m, i, v);
            nd[ix].r = nd[prev].r;
        }
        else {
            nd[ix].l = nd[prev].l;
            nd[ix].r = update(nd[prev].r, m + 1, r, i, v);
        }
        return ix;
    }
    ll query(int prev, int ix, int nl, int nr, int l, int r) {
        if(nl > r || nr < l) return 0;
        if(nl >= l && nr <= r) return nd[ix].v - nd[prev].v;
        int m = nl + nr >> 1;
        return query(nd[prev].l, nd[ix].l, nl, m, l, r) + query(nd[prev].r, nd[ix].r, m + 1, nr, l, r);
    }
    int kth(int i1, int i2, int l, int r, int k) {
        while (l ^ r) {
            int cnt = nd[nd[i2].l].v - nd[nd[i1].l].v;
            int m = l + r >> 1;
            if (k <= cnt) r = m, i1 = nd[i1].l, i2 = nd[i2].l;
            else l = m + 1, k -= cnt, i1 = nd[i1].r, i2 = nd[i2].r;
        }
        return l;
    }
}

pst::root[0] = pst::init(0, n);
