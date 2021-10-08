struct node {
	node* l, * r, * p;
	ll val, mn, mx, sum;
	bool inv;
	int sz;
	// 초기화 신경쓰기
	node(int val = 0) : l(NULL), r(NULL), p(NULL), sz(1), val(val), inv(0) {};
};

ll n, q, a[NMAX], op, l, r, x;
node* tree;
node* idx[NMAX];

// rotate 후에 값들을 갱신
void pull(node* x) {
	x->sz = 1;
	x->sum = x->mn = x->mx = x->val;

	if (x->l) {
		x->sz += x->l->sz;
		x->sum += x->l->sum;
		x->mn = min(x->mn, x->l->mn);
		x->mx = max(x->mx, x->l->mx);
	}
	if (x->r) {
		x->sz += x->r->sz;
		x->sum += x->r->sum;
		x->mn = min(x->mn, x->r->mn);
		x->mx = max(x->mx, x->r->mx);
	}
	return;
}

// lazy값을 업데이트(inv 업데이트)
void push(node* x) {
	if (!x->inv) return;
	swap(x->l, x->r);
	if (x->l) x->l->inv ^= 1;
	if (x->r) x->r->inv ^= 1;
	x->inv = 0;
	return;
}

void rotate(node* x) {
	node* p = x->p;
	node* b;

	push(p);
	push(x);
	// x와 p를 rotate
	// x, p의 l, r 갱신
	if (x == p->l) {
		p->l = b = x->r;
		x->r = p;
	}
	else {
		p->r = b = x->l;
		x->l = p;
	}

	// x, p, (b)의 parent 갱신
	x->p = p->p;
	p->p = x;
	if (b) b->p = p;

	// 기존 p의 부모의 입장에서 자식을 갱신
	if (x->p) {
		if (x->p->l == p) x->p->l = x;
		else x->p->r = x;
	}
	else tree = x;

	// rotate가 끝난 후 바뀐 위치에 맞게 값을 갱신
	pull(p); pull(x);
	return;
}

void splay(node* x) {
	while (x->p) {
		node* p = x->p;
		node* g = p->p;
		if (g) {
			// zig-zag step | zig-zig step
			if ((p->l == x) ^ (g->l == p)) rotate(x);
			else rotate(p);
		}
		rotate(x);
	}
	return;
}

// tree 초기화
void init_tree() {
	// 왼쪽 더미 노드
	node* x;
	x = tree = new node();

	// n : 오른쪽 더미 노드
	for (int i = 1; i <= n + 1; i++) {
		x->r = new node(a[i]);
		x->r->p = x;
		x = x->r;
		idx[i] = x;
	}
	while (x) {
		pull(x); x = x->p;
	}
	return;
}

// k번째 원소 찾기 (0-based, 더미노드 고려)
void findk(int k) {
	node* x = tree;
	push(x);

	while (1) {
		while (x->l && x->l->sz > k) {
			x = x->l; push(x);
		}
		if (x->l) k -= x->l->sz;
		if (!k--) break;
		x = x->r;
		push(x);
	}
	splay(x);
	return;
}

// 구간 [l, r]을 모아주는 함수
// tree->r->l의 서브트리에 구간 [l, r]이 모여있음
void gather(int l, int r) {
	findk(l - 1);
	// t(루트) : l - 1번째 원소
	// t의 오른쪽 서브트리(l- )를 임시로 잘라줌
	node* t = tree;
	tree = t->r;
	tree->p = nullptr;

	findk(r - l + 1);
	t->r = tree;
	tree->p = t;
	// 다시 tree(루트)를 복원
	tree = t;
	return;
}

// i번째 원소 앞에 val을 삽입(0-based, 더미노드 고려)
void insert(int i, ll val) {
	findk(i);
	node* x = new node(val);
	x->p = tree; x->l = tree->l;
	tree->l->p = x; tree->l = x;
	splay(x);
	return;
}

// i번째 원소 삭제(0-based, 더미노드 고려)
void erase(int i) {
	gather(i, i);
	node* x = tree->r->l;
	tree->r->l = NULL;
	delete x;
	return;
}

ll Min(int l, int r) {
	gather(l, r);
	return tree->r->l->mn;
}

ll Max(int l, int r) {
	gather(l, r);
	return tree->r->l->mx;
}

ll Sum(int l, int r) {
	gather(l, r);
	return tree->r->l->sum;
}

void Rev(int l, int r) {
	gather(l, r);
	tree->r->l->inv ^= 1;
	return;
}
