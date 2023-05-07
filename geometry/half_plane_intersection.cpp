typedef long double ld;
const double eps = 1e-10, inf = 1e9;
struct pd{
    ld x, y;
    pd operator +(pd t){return {x + t.x, y + t.y};}
    pd operator -(pd t){return {x - t.x, y - t.y};}
    ld operator *(pd t){return x * t.x + y * t.y;}
    ld operator /(pd t){return x * t.y - y *t.x;}
    ld sz() {return sqrt(x * x + y * y);}
};

struct line{
    pd p, d;
    ld a;
    
    line() {}
    //두 점을 지나는 직선
    line(pd p,pd q) : p(p), d(q - p){
        a = atan2l(d.y, d.x);
    }
    // half plane 
    // 점이 반평면 밖에 있는 지 확인
    bool out(pd t){return d / (t - p) < eps;}
    // 각도 순으로 정렬
    bool operator < (line t){return a < t.a;}
};

// 두 직선의 교점 구하기 (평행x)
pd interPoint(line a, line b){
    long double t = ((b.p - a.p) / b.d) / (a.d / b.d);
    a.p.x += t * a.d.x;
    a.p.y += t * a.d.y;
    return a.p;
}

// 반평면 교집합 구하기 O(NlogN)
vector<pd> half_plane(vector<line> v){
    // unbounded case 일 경우 boundary를 만들어주기
    /* 
    pd box[4] = {
        pd{inf, inf},
        pd{-inf, inf},
        pd{-inf, -inf},
        pd{inf, -inf},
    };
    for(int i = 0; i < 4; i++) v.push_back(line(box[i], box[(i + 1) % 4]));
    */

    vector<pd> ret;
    deque<line> dq;
    sort(all(v));
    for(auto&l : v){
        while(dq.size() > 1 && l.out(interPoint(dq[dq.size() - 2], dq.back()))) dq.pop_back();
        while(dq.size() > 1 && l.out(interPoint(dq[0], dq[1]))) dq.pop_front();

        // 평행한 두 직선 예외 처리하기
        if(dq.size() && fabsl(dq.back().d / l.d) < eps){
            if(dq.back().d * l.d < 0.0) return ret;
            
            if(l.out(dq.back().p)) dq.pop_back();
            else continue;
        }
        dq.emplace_back(l);
    }

    while(dq.size() > 2 && dq[0].out(interPoint(dq[dq.size() - 2], dq.back()))) dq.pop_back();
    while(dq.size() > 2 && dq.back().out(interPoint(dq[0], dq[1]))) dq.pop_front();
    if(dq.size() < 3) return ret;
    for(int i = 0, n = dq.size(); i < n; i++)
        ret.emplace_back(interPoint(dq[i], dq[(i + 1) % n]));
    return ret;
}
