// 최댓값 기준
const ll inf = 1e18;
struct line{
	ll a, b;
	ll get(ll x){return a * x + b;}
};

struct node{
	ll lc, rc, l, r;
	line ln;
};
vector<node> Tree;
int t;  // Tree 노드 개수

void upd_line(int ix, line hi){
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
		upd_line(Tree[ix].rc, lw);
	}
	else{
		Tree[ix].ln = lw;
		if(Tree[ix].lc == -1){
			Tree[ix].lc = ++t;
			Tree.push_back({-1, -1, l, m, {0, -inf}});   // to modify : 더미 선분
		}
		upd_line(Tree[ix].lc, hi);
	}
	return;
}

ll qry(int ix, ll x){
	if(ix == -1) return -inf;
	ll m = (Tree[ix].l + Tree[ix].r) >> 1;
	if(x <= m) return max(Tree[ix].ln.get(x), qry(Tree[ix].lc, x));
	else return max(Tree[ix].ln.get(x), qry(Tree[ix].rc, x));
}

// main 함수에서 더미 선분 추가해주기
Tree.push_back({-1, -1, 0, e, {0, -inf}});
