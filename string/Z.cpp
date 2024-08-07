int Z[NMAX];

void funZ(string& s){
    int n = s.size();
    Z[0] = n;
    for(int i = 1, l = 0, r = 0; i < n; i++){
        if(i <= r) Z[i] = min(Z[i - l], r - i + 1);
        while(i + Z[i] < n && s[i + Z[i]] == s[Z[i]]) Z[i]++;
        if(r < i + Z[i] - 1){
            l = i; r = i + Z[i] - 1;
        }
    }
    return;
}
