// 1. 정수 범위 내 탐색
ll s = 0, e = T, l, r;
while(s + 3 <= e){
    l = (s + s + e) / 3;
    r = (s + e + e) / 3;
    if(f(l) > f(r)) s = l;
    else e = r;
}
for(int i = s; i <= e; i++) {
    // answer 갱신
}

// 2. 실수 범위 내 탐색 (실수 오차를 피하기 위해서 for문으로 횟수로 돌기)
ld s = 0, e = 3000, l, r;
for(int i = 0; i < 100; i++){
    l = (s + s + e) / 3;
    r = (s + e + e) / 3;
    if(f(l) > f(r)) s = l;
    else e = r;
}
