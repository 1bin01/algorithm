struct node {
	ll l, r, m, s;
};
vector<node> seg;

node merge(node a, node b) {
	return{
		max(a.l, a.s + b.l),
		max(b.r, b.s + a.r),
		max({a.m, b.m, a.r + b.l }),
		a.s + b.s
	};
}

void upd(int ix, ll x) {
	ix += base; x += seg[ix].m;
	seg[ix] ={ x, x, x, x }; ix /= 2;
	while(ix) {
		seg[ix] = merge(seg[ix * 2], seg[ix * 2 + 1]);
		ix /= 2;
	}
	return;
}
