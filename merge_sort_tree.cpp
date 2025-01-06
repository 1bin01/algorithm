const int b = 1 << 17;
int n, a[NMAX];
vector<int> seg[b * 2];

// initialize segment tree O(nlogn)
for(int i = 1; i <= n; i++) seg[b + i].emplace_back(a[i]);
for(int i = b - 1; i; i--){
	seg[i].resize(seg[i * 2].size() + seg[i * 2 + 1].size());
        merge(all(seg[i * 2]), all(seg[i * 2 + 1]), seg[i].begin());
}

// query O((logn^)2)
// example : 구간 [l, r]에서 k보다 큰 원소의 개수
int qry(int l, int r, int k){
    int ret = 0;
    l += b; r += b;
    while(l <= r){
        if(l & 1){
            auto it = upper_bound(all(seg[l]), k);
            ret += seg[l++].end() - it;
        }
        if(!(r & 1)){
            auto it = upper_bound(all(seg[r]), k);
            ret += seg[r--].end() - it;   
        }
        l /= 2; r /= 2;
    }
    return ret;
}
