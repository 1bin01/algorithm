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
 
int go(ll cost){
    sz = ii = 0;
    // initial state update
    auto&[x, y] = v[0];
    upd(-2 * x, x * x, 0);
  
    for(int i = 1; i <= n; i++){
      // 수식 계산
        dp[i] = f({Xval}) + {Pval} + cost;
        if(i < n){
            // 수식 계산
            upd({mval}, {pval}, cnt[ii] + 1);
        }
    }
    return cnt[ii] + 1;
}

// 이분 탐색
ll l = 0, r = ?, mid;
    while(l < r){
        mid = (l + r) / 2;
        if(go(mid) <= k) r = mid;
        else l = mid + 1;
    }
    go(l);
return dp[n] - l * k;
