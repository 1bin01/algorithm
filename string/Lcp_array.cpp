int isa[NMAX], lcp[NMAX], l;
string s;

void getLCP(string& s){
    l = 0;

    for(int i = 0; i < n; i++) isa[sa[i]] = i;
    for(int i = 0; i < n; i++, l = max(l - 1, 0)){
        if(!isa[i]) continue;
        for(int j = sa[isa[i] - 1]; s[i + l] == s[j + l]; l++);
        lcp[isa[i]] = l;
    }
    return;
}
