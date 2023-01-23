/*
3가지 조건을 만족할 때 O(N^3) -> O(N^2)
1. dp[i][j] = min(dp[i][k] + dp[k + 1][j] + C[i][j])
2. C가 monge array -> C[a][c] + C[b][d] <= C[a][d] + C[b][c]
3. 단조성 C[b][c] <= C[a][d]
*/

for(int i = 1; i <= n; i++) opt[i][i] = i;
    for(int d = 1; d < n; d++)
        for(int i = 1; i + d <= n; i++){
            int j = i + d;
            dp[i][j] = 1e9;
            for(int pt = opt[i][j - 1]; pt <= opt[i + 1][j]; pt++)
                if(pt < j){
                    int x = dp[i][pt] + dp[pt + 1][j] + p[j] - p[i - 1];
                    if(x < dp[i][j]){
                        dp[i][j] = x;
                        opt[i][j] = pt;
                    }
                }
        }
