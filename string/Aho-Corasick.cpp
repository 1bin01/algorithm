const int LM = 1e5 + 5;
int tri[LM][26], term[LM], fail[LM], t;

void ins(string & s){
    int sz = s.size(), ix = 0;
    for(int i = 0; i < sz; i++){
        int& nx = tri[ix][s[i] - 'a'];
        if(nx == -1) nx = ++t;
        ix = nx;
    }
    term[ix] = 1;
    return;
}

void getpi(){
    queue<int> q; q.emplace(0);
    while(q.size()){
        int x = q.front(); q.pop();
        for(int i = 0; i < 26; i++){
            int nx = tri[x][i];
            if(nx == -1) continue;
            if(x){
                int j = fail[x];
                while(j && tri[j][i] == -1) j = fail[j];
                if(tri[j][i] != -1) fail[nx] = tri[j][i];
            }
            if(term[fail[nx]]) term[nx] = 1;
            q.emplace(nx);
        }
    }
    return;
}

int find(string & s){
    int sz = s.size(), ix = 0, c;
    for(int i = 0; i < sz; i++){
        c = s[i] - 'a';
        while(ix && tri[ix][c] == -1) ix = fail[ix];
        if(tri[ix][c] != -1) ix = tri[ix][c];
        if(term[ix]) return 1;
    }
    return 0;
}
