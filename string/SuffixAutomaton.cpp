struct SuffixAutomaton{
    struct node{
        int nx[26], len, link;
        node() {
            memset(nx, -1, sizeof(nx));
            len = 0; link = -1;
        }
        node(int len_, int link_){
            memset(nx, -1, sizeof(nx));
            len = len_;
            link = link_;
        }
    };
    vector<node> sa;
    int x;   // 전체 문자열의 index

    SuffixAutomaton(){
        x = 0;
        sa.emplace_back(node());
    }
    void add(int c){
        assert(0 <= c && c < 26);
        int p = x;
        x = sa.size();
        sa.emplace_back(node(sa[p].len + 1, 0));    //  new node x
        while(p >= 0 && sa[p].nx[c] == -1){
            sa[p].nx[c] = x;
            p = sa[p].link;
        }
        if(p != -1){
            int prv = sa[p].nx[c], upd = prv;
            if(sa[p].len + 1 < sa[prv].len){ // split prv -> upd + prv
                // new node upd
                upd = sa.size();
                node nd = sa[prv];
                nd.len = sa[p].len + 1;
                sa.emplace_back(nd);
                for(int i = p; i >= 0 && sa[i].nx[c] == prv; i = sa[i].link) sa[i].nx[c] = upd;
                sa[prv].link = upd;
            }
            sa[x].link = upd;
        }
        return;
    }
} S;
