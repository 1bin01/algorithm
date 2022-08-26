#include <bits/stdc++.h>

using namespace std;

#define all(v) v.begin(), v.end()
typedef long long ll;
const int LM = 25000005;
int n, m, lv[LM], term[LM], t, fail[LM], p[300005], ans, cur;
vector<pair<int, char>> tri[LM];
string s, ss;

void ins(string & s){
    int ix = 0;
    for(int i = 0; i < s.size(); i++){
        int nx = -1;
        for(auto&[x, c] : tri[ix])
            if(s[i] == c) nx = x;
        if(nx == -1) {
            tri[ix].emplace_back(++t, s[i]);
            nx = t;
        }
        ix = nx;
    }
    term[ix] = 1;
    return;
}

void getpi(){
    queue<int> q; q.emplace(0);
    while(q.size()){
        int x = q.front(); q.pop();
        for(auto& [nx, c] : tri[x]){
            if(x){
                int j = fail[x], nj = -1;
                for(;j; j = fail[j]){
                    for(auto& [nj, cj] : tri[j])
                        if(cj == c) {
                            nj = cj;
                            break;
                        }
                    if(nj != -1) break;
                }
                
                if(nj != -1) {
                    fail[nx] = nj;
                    term[nx] |= term[nj];
                }
            }
            q.emplace(nx);   
        }
    }
    return;
}

void find(){
    int ix = 0, c;
    for(int i = 0; i < n; i++){
        c = s[i] - 'a';
        while(ix && tri[ix][c] == -1) ix = fail[ix];
        if(tri[ix][c] != -1) ix = tri[ix][c];
        if(term[ix]){
            p[i - lv[ix] + 1]++;
            p[i + 1]--;
        }
    }
    return;
}
 
int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> s >> m;
    memset(tri, -1, sizeof(tri));
    while(m--){
        cin >> ss;
        ins(ss);
    }
    getpi();
    find();
    for(int i = 0; i < n; i++){
        cur += p[i];
        if(!cur) ans++;
    }
    cout << ans;
    return 0;
}
