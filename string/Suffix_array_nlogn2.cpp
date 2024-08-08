// 배열 크기는 2배로 잡기
int n, sa[NMAX], g[NMAX], tmp[NMAX];
string s;

void getSA(string& s){
    int n = s.size();
    for(int i = 0; i < n; i++){
        g[i] = s[i] - 'a' + 1;
        sa[i] = i;
    }

    for(int d = 1; d < n; d *= 2){
        auto cmp = [&](int i, int j){
            if(g[i] == g[j]) return g[i + d] < g[j + d];
            else return g[i] < g[j];
        };
        sort(sa, sa + n, cmp);

        tmp[sa[0]] = 1;
        for(int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        for(int i = 0; i < n; i++) g[i] = tmp[i];
        if(g[sa[n - 1]] == n) break;
    }
    return;
}
