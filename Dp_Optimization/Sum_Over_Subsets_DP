ll a[1 << NMAX], S[1 << NMAX], dp[1 << NMAX][NMAX];

// naive iterative  -time complexity : O(n2^n), memory : O(n2^n)
for(int mask = 0; mask < (1 << n); mask++){
    dp[mask][0] = a[mask];
    for(int i = 0; i < n; i++){
        dp[mask][i + 1] = dp[mask][i];
        if(mask & (1 << i)) dp[mask][i] += dp[mask ^ (1 << i)][i - 1];
    }
    S[mask] = dp[mask][n];
}

// optimized  -memory : O(2^n)
for(int i = 0; i < (1 << n); i++) S[i] = a[i];
for(int i = 0; i < n; i++)
    for(int mask = 0; mask < (1 << n); mask++)
        if(mask & (1 << i)) S[mask] += S[mask ^ (1 << i)];
