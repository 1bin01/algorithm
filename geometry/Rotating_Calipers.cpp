ll dist(pt a, pt b){ return (b - a).sz(); }

// 회전하는 캘리퍼스 O(n)
// ConvexHull에서 두 점 사이의 거리의 최댓값 구하기
ll RotateC(vector<pt> v){
    int n = v.size();
    if(n <= 1) return 0;
    if(n == 2) return dist(v[0], v[1]);
    ll mxd = 0;
    for(int i = 0, j = 0; i < n; i++){
        while((v[(i + 1) % n] - v[i]) / (v[(j + 1) % n] - v[j]) >= 0) mxd = max(mxd, dist(v[i], v[j])), j = (j + 1) % n;
        mxd = max(mxd, dist(v[i], v[j]));
    }
    return mxd;
}

// ConvexHull을 포함하는 직사각형의 둘레(넓이)의 최솟값 구하기
// 4개버전
ld dist(pt a, pt b){return a / b / a.sz();}
ld dist2(pt a, pt b){return a * b / a.sz();}
ld RotateC(vector<pt>& v){
    ld ans = 1e18;
    int n = v.size();
    if(v.size() <= 1) return 0;
    if(v.size() == 2) return 2 * (v[1] - v[0]).sz();
    
    for(int i = 0, j = 0, k = 0, l = 0; i < n; i++){
        while((v[(i + 1) % n] - v[i]) / (v[(j + 1) % n] - v[j]) >= 0) {
            if(l == j) l = (l + 1) % n;
            j = (j + 1) % n;
        }
        while((v[(i + 1) % n] - v[i]) * (v[(k + 1) % n] - v[k]) >= 0) k = (k + 1) % n;
        while((v[i] - v[(i + 1) % n]) * (v[(l + 1) % n] - v[l]) >= 0) l = (l + 1) % n;
        ld h = dist(v[(i + 1) % n] - v[i], v[j] - v[i]);
        ld w = dist2(v[(i + 1) % n] - v[i], v[k] - v[i]) + dist2(v[i] - v[(i + 1) % n], v[l] - v[i]);
        ans = min(ans, h + w);
        if(k == i) k = (k + 1) % n;
    }
    return 2 * ans;;
}
