const int LM = 1e6 + 5; // 길이는 string size * 2로 잡기
string s, t;
int n, r[LM], e, x, ans;

 s += '#';
 for(int i = 0; i < t.size(); i++){
     s += t[i]; s += '#';
 }

n = s.size();
for(int i = 0; i < n; i++){
    if(i <= e) r[i] = min(r[2 * x - i], e - i);
    while(i - r[i] - 1 >= 0 && i + r[i] + 1 < n && s[i - r[i] - 1] == s[i + r[i] + 1]) r[i]++;
    if(i + r[i] > e){
        e = i + r[i]; x = i;
    }
}
