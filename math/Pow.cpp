const ll mod = 1e9 + 7;

// calculate x ^ k
// time complexity : O(log(k))
ll Pow(ll x, ll k) {		
	ll ret = 1;
	while (k) {
		if (k & 1) {
			ret *= x; ret %= mod;
		}
		x = x * x % mod; k >>= 1;
	}
	return ret;
}
