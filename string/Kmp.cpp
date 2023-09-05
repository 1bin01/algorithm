// time complexity : O(n + m)
int n, m, fail[NMAX];
string s, w;

// pi 배열 구하기
memset(fail, 0, sizeof(fail));
for(int i = 1, j = 0; i < m; i++){
	while(j && w[i] != w[j]) j = fail[j - 1];
	if(w[i] == w[j]) fail[i] = ++j;
}

// kmp 패턴매칭
for(int i = 0, j = 0; i < n; i++){
	while(j && s[i] != w[j]) j = fail[j - 1];
	if(s[i] == w[j]) j++;
	v[i] = j;
}
