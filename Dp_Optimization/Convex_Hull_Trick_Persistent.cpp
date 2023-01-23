// 최댓값 기준

ll n, m[NMAX], p[NMAX], ii[NMAX], t[NMAX], tt[NMAX];
stack<ll> st;
double cross(int b, int a){return 1.0 * (p[b] - p[a]) / (m[a] - m[b]);}

int insert(ll mm, ll pp, int e){
    int l = 0, r = e, mid;
    m[n + 1] = mm; p[n + 1] = pp;
    
    while(l < r){
        mid = (l + r) / 2;
        if(cross(mid, mid + 1) >= cross(mid + 1, n + 1)) r = mid;
        else l = mid + 1;
    }
    return l + 1;
}

ll go(ll x, int e){
    int l = 0, r = e, mid;
    
    while(l < r){
        mid = (l + r) / 2;
        if(cross(mid, mid + 1) <= x) l = mid + 1;
        else r = mid;
    }
    return m[l] * x + p[l];
}
