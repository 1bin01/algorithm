// time complexity : O(logmin(a, b))
// ax + by = d : gcd(a, b)가 d의 약수이면 위 식을 만족하는 (x, y)쌍이존재

ll Euclid(ll a,ll b,ll &x,ll &y){
    if(!b){
        x = 1, y = 0;
        return a;
    }
    ll d = Euclid(b, a % b, y, x);
    y -= a / b *x;
    return d;
}

ll x, y;
ll g = Euclid(a, b, x, y);
