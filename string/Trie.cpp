const int LM = 1e6 + 5;
int n, tri[LM][26], cnt[LM], t;

void ins(string & s){
    int ix = 0;
    for(int i = 0; i < s.size(); i++){
        int& nx = tri[ix][s[i] - 'a'];
        if(nx == -1) nx = ++t;
        ix = nx;
    }
    cnt[ix]++;
}

int find(string& s) {
    int ix = 0;
    for (int i = 0; i < s.size(); i++) {
        int& nx = tri[ix][s[i] - 'a'];
        if (nx == -1) return 0;
        ix = nx;
    }
    if (cnt[ix]) return 1;
}

// main : memset(tri, -1, sizeof(tri));
