// dp[i][j] : j개를 i개의 구간으로 나누는 dp에서 i <= k의 조건이 있을 때 이 조건을 없애 차원 줄이기
// 아래는 CHT + Aliens Trick 문제의 예시 코드

// 기울기, x좌표 단조 증가 O(n)
// 최소값 upper bound convexhull
ll n, x, y, bx = -1, dp[NMAX];
vector<pair<ll, ll>> v;
ll m[NMAX], p[NMAX], sz, ii, cnt[NMAX];
int bad(int a, int b, int c){ return (p[b] - p[a]) * (m[b] - m[c]) >= (m[a] - m[b]) * (p[c] - p[b]);}
ll get(int i, ll x){return m[i] * x + p[i];}

void upd(ll mm, ll pp, int c){
    m[sz] = mm;
    p[sz] = pp;
    cnt[sz] = c;
    while(sz > 1 && bad(sz - 2, sz - 1, sz)){
        m[sz - 1] = m[sz];
        p[sz - 1] = p[sz];
        cnt[sz - 1] = cnt[sz];
        if(--sz == ii) ii--;
    }
    sz++;
    return;
}

ll f(ll x){
    while(ii + 1 < sz && get(ii, x) > get(ii + 1, x)) ii++;
    return get(ii, x);
}
 
pair<ll, ll> go(ll cost){
    sz = ii = 0;
    // initial state update
    auto&[x, y] = v[0];
    upd(-2 * x, x * x, 0);
    
    for(int i = 1; i <= n; i++){
        // 수식 계산
        // p : <dp[i], cnt[i]>
        pair<ll,ll> p = {f({Xval}) + {Pval} + cost, cnt[ii] + 1};
        if(i < n){
            // 수식 계산
            upd({mval}, {pval}, p.second);
        }
        else return p; 
    }
    return {-1, -1};
}

// 이분 탐색 (한 접선에 대응되는 점이 여럿인 경우 주의해서 처리)
ll l = 0, r = ?, mid, ans = -1e18;
while(l < r){
    mid = (l + r) / 2;
    auto p = go(mid);
    ans = max(ans, p.first - k * mid);
    if(p.second <= k) r = mid;
    else l = mid + 1;
}
return ans;
