// 구간합 세그
const int b = 1 << 18;
ll seg[b * 2];

void upd(int ix, ll v){
    ix += b;
    while(ix){
        seg[ix] += v;
        ix /= 2;
    }
    return;
}
 
ll sum(int l, int r){
    ll ret = 0;
    l += b; r += b;
    while(l <= r){
        if(l & 1) ret += seg[l++];
        if(!(r & 1)) ret += seg[r--];
        l /= 2; r /= 2;
    }
    return ret;
}

// k번째 원소 찾기
int find(int k){
    int ix = 1;
    while (ix < b) {
        ix <<= 1;
        if (seg[ix] < k) k -= seg[ix++];
    }
    return ix - b;
}
