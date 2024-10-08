// 배열 크기는 2배로
// d[n] ~ d[2 * n] 값은 0이여야 함.(초기화 주의)
// m = max(n, 128)
int n, m, sa[NMAX], g[NMAX], cnt[NMAX], idx[NMAX], tmp[NMAX];
string s;

void getSA(string& s){
    n = s.size(); m = max(n, 128);
    for(int i = 0; i < n; i++) g[i] = s[i], sa[i] = i;
    for(int i = n; i <= 2 * n; i++) g[i] = 0;

    for(int d = 1; d < n; d *= 2){
        auto cmp = [&](int i, int j){
            if(g[i] == g[j]) return g[i + d] < g[j + d];
            else return g[i] < g[j];
        };

        for(int i = 0; i < m; i++) cnt[i] = 0;
        for(int i = 0; i < n; i++) cnt[g[i + d]]++;
        for(int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; i--) idx[--cnt[g[i + d]]] = i;

        for(int i = 0; i < m; i++) cnt[i] = 0;
        for(int i = 0; i < n; i++) cnt[g[i]]++;
        for(int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--cnt[g[idx[i]]]] = idx[i];

        tmp[sa[0]] = 1;
        for(int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        for(int i = 0; i < n; i++) g[i] = tmp[i];
        if(g[sa[n - 1]] == n) break;
    }
    return;
}
