struct pt{
    ll x, y;
    pt operator + (pt t){return {x + t.x, y + t.y};}
    pt operator - (pt t){return {x - t.x, y - t.y};}
    ll operator * (pt t){return x * t.x + y * t.y;}
    ll operator / (pt t){return x * t.y - y * t.x;}
};

int ccw(pt a, pt b, pt c){
    ll t = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return (t < 0) - (t > 0);
}

// 다각형의 넓이 O(n)
double area(vector<pt> v){
    double ret = 0;
    for(int i = 0, n = v.size(); i < n; i++)
        ret += v[i] / v[(i + 1) % n];
    return abs(ret) / 2.0;
}

// 삼각형 내부의 점 판별 O(1)
int inTriangle(vector<pt> t, pt p){
    int sign[3];
    for(int i = 0; i < 3; i++)
        sign[i] = ccw(t[i], t[(i + 1) % 3], p);
    if(sign[0] == sign[1] && sign[1] == sign[2]) return -1;
    for(int i = 0; i < 3; i++) if(sign[i] * sign[(i + 1) % 3] == -1) return 1;
    return 0;
}

