// 1 <= x <= b인 경우, array를 이용한 구현

const int b = 1 << 18;
int n, q, S[b], P[b], E[b], R[b];
char c;
struct Line {
    ll a, b;
    // 함숫값 return
    ll operator ()(ll x){return a * x + b}
}LT[b * 2];

// 최댓값 기준
void ins(int ix, int l, int r, Line line) {
    if(l == r) {
        if(line(l) > LT[ix](l)) LT[ix] = line;
        return;
    }
    int m = (l + r) >> 1;
    // 기울기가 큰 놈을 삽입
    if(LT[ix].a > line.a) swap(LT[ix], line);
    if(LT[ix](m) < line(m)) {
        swap(LT[ix], line);
        ins(ix * 2, l, m, line);
    }
    else ins(ix * 2 + 1, m + 1, r, line);
    return;
}

ll qry(int ix, int l, int r, ll x) {
    if(l == r) return LT[ix](x);
    int m = (l + r) >> 1;
    if(x < m) return max(LT[ix](x), qry(ix * 2, l, m, x));
    else return max(LT[ix](x), qry(ix * 2 + 1, m + 1, r, x));
}
