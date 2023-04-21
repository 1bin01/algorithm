struct pt{
    ll x, y;
    pt operator + (pt t){return {x + t.x, y + t.y};}
    pt operator - (pt t){return {x - t.x, y - t.y};}
    ll operator * (pt t){return x * t.x + y * t.y;}
    ll operator / (pt t){return x * t.y - y * t.x;}
    bool operator == (pt t){return x == t.x && y == t.y;}
    bool operator <(pt t){return x == t.x ? y < t.y : x < t.x;}
    ll sz(){return x * x + y * y;}
};

int ccw(pt a, pt b, pt c){
    b = b - a; c = c - a;
    return (b / c > 0) - (b / c < 0);
}
int ccw2(pt a, pt b){ return (a / b > 0) - (a / b < 0);}

// 선분 교차 판정
bool intersect(pt p1, pt p2, pt p3, pt p4){
    int a = ccw(p1, p2, p3) * ccw(p1, p2, p4);
    int b = ccw(p3, p4, p1) * ccw(p3, p4, p2);
    if(!a && !b){
        if(p2 < p1) swap(p1, p2);
        if(p4 < p3) swap(p3, p4);
        return !(p2 < p3 || p4 < p1);
    }
    return a <= 0 && b <= 0;
}

// 두 선분의 교점 구하기
bool getpoint(pt p1, pt p2, pt p3, pt p4, pt& p){
    double d = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
    double t = (p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x);
    double s = (p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x);
    if(!d){
        // t == 0 : 동일한 선
        
        // t != 0 : 평행
        if(p2 < p1) swap(p1, p2);
        if(p4 < p3) swap(p3, p4);
        
        // 한 점에서 만나는 경우
        if(p2 == p3) {
            p = p2; return 1;
        }    
        if(p4 == p1){
            p = p4; return 1;
        }
        return 0;
    }
    t /= d; s /= d;
    // t >= 0 && t <= 0 : 교점 존재
    p.x = p1.x + (p2.x - p1.x) * t;
    p.y = p1.y + (p2.y - p1.y) * t;
    return 1;
}

// 두 점 사이의 거리 (제곱)
ll dist(pt& a, pt& b){
    pt d = b - a;
    return d.sz();
}

// 직선(선분)과 점의 거리
double linedist(pt a, pt b, pt c){
    pt t = b - a;
    // 선분일 경우
    if(t * (c - a) <= 0) return sqrt(dist(a, c));
    if(t * (c - b) >= 0) return sqrt(dist(b, c));
    //   
    return abs(t / (c - a)) / sqrt(t.sz());
}

// 다각형의 넓이 O(n)
double area(vector<pt>& v){
    double ret = 0;
    for(int i = 0, n = v.size(); i < n; i++)
        ret += v[i] / v[(i + 1) % n];
    return abs(ret) / 2.0;
}

// ConvexHull O(nlogn)
vector<pt> hull(vector<pt> v){
    int ix = min_element(all(v)) - v.begin();
    swap(v[0], v[ix]);
    vector<pt> st;
    
    sort(v.begin() + 1, v.end(), [&] (pt& a, pt& b){
       pt x = a - v[0], y = b - v[0];
       return x / y ? x / y > 0 : x.sz() < y.sz();
    });
    for(auto& p : v){
        while(st.size() > 1 && ccw(st[st.size() - 2], st.back(), p) <= 0) st.pop_back();
        st.emplace_back(p);
    }
    
    /*
    # 마지막 점들이 일직선 상에 있는 경우에 예외처리를 해야 하는 경우
    int i = v.size() - 1;
    while(i >= 1 && !ccw(v[0], v[i], v[i - 1])) i--;
    reverse(v.begin() + i, v.end());
    */
    return st;
}

// 삼각형 내부의 점 판별 O(1)
int inTriangle(vector<pt>& t, pt p){
    int sign[3];
    for(int i = 0; i < 3; i++)
        sign[i] = ccw(t[i], t[(i + 1) % 3], p);
    if(sign[0] == sign[1] && sign[1] == sign[2]) return -1;
    for(int i = 0; i < 3; i++) if(sign[i] * sign[(i + 1) % 3] == -1) return 1;
    return 0;
}

// 볼록 다각형 내부의 점 판별 O(n)
int inside(pt p, vector<pt>& v){
    if(v.size() < 3) return 0;
    for(int i = 0, n = v.size(); i < n; i++)
        if(ccw(v[i], v[(i + 1) % n], p) <= 0) return 0;
    return 1;
}

// 볼록 다각형 내부의 점 판별 O(logn)
int inside(pt p, vector<pt>& v){
    int n = v.size();
    if(n < 3 || ccw(v[0], v[1], p) < 0 || ccw(v[0], v[n - 1], p) > 0) return 0;
    
    int l = 2, r = n - 1, m;
    while(l < r){
        m = (l + r) / 2;
        if(ccw(v[0], v[m], p) < 0) r = m;
        else l = m + 1;
    }
    return ccw(v[l - 1], p, v[l]) < 0;
}

// 회전하는 캘리퍼스 O(n)
ll RotC(vector<pt> v){
    int n = v.size();
    if(n == 2) return dist(v[0], v[1]);
    ll mx = 0;
    for(int i = 0, j = 0; i < n; i++){
        while(ccw2(v[(i + 1) % n] - v[i], v[(j + 1) % n] - v[j]) >= 0) mx = max(mx, dist(v[i], v[j])), j = (j + 1) % n;
        mx = max(mx, dist(v[i], v[j]));
    }
    return mx;
}
