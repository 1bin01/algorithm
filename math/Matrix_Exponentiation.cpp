// 행렬 거듭제곱
// time complexity : O(n^3 * log(k))

typedef vector<vector<ll>> mat;
const ll mod = 1e9 + 7;

mat operator *(const mat & a, const mat & b){
    int sz = a.size();
    mat ret(sz, vector<ll> (sz));
    
    for(int i = 0; i < sz; i++)
        for(int j = 0; j < sz; j++)
            for(int k = 0; k < sz; k++)
                ret[i][j] += a[i][k] * b[k][j], ret[i][j] %= mod;
    return ret;
}

mat matpow(mat a, ll k){
    int sz = a.size();
    mat ret(sz, vector<ll> (sz));
    for(int i = 0; i < sz; i++) ret[i][i] = 1;
    while(k){
        if(k & 1) ret = ret * a;
        k /= 2; a = a * a;
    }
    return ret;
}
