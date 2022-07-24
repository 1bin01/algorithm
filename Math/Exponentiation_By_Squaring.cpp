typedef vector<vector<ll>> mat;
const ll mod = 1e9 + 7;

mat operator *(const mat & a, const mat & b){
    ll sz = a.size();
    mat c(sz, vector<ll> (sz));
    
    for(int i = 0; i < sz; i++)
        for(int j = 0; j < sz; j++)
            for(int k = 0; k < sz; k++)
                c[i][j] += a[i][k] * b[k][j], c[i][j] %= mod;
    return c;
}

mat power(mat a, ll k){
    ll sz = a.size();
    mat c(sz, vector<ll> (sz));
    for(int i = 0; i < sz; i++) c[i][i] = 1;
    while(k){
        if(k & 1) c = c * a;
        k /= 2; a = a * a;
    }
    return c;
}
