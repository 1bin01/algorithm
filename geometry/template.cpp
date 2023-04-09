struct pt{
    ll x, y;
    pt operator + (pt t){return {x + t.x, y + t.y};}
    pt operator - (pt t){return {x - t.x, y - t.y};}
    ll operator * (pt t){return x * t.x + y * t.y;}
    ll operator / (pt t){return x * t.y - y * t.x;}
};

int ccw(pt a, pt b, pt c){
    b = b - a; c = c - a;
    ll t = b / c;
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



#include <bits/stdc++.h>

using namespace std;

#define all(v) v.begin(), v.end()
typedef long long ll;

struct pt{
    ll x, y;
    pt operator + (pt t){return {x + t.x, y + t.y};}
    pt operator - (pt t){return {x - t.x, y - t.y};}
    ll operator * (pt t){return x * t.x, y * t.y;}
    ll operator / (pt t){return x * t.y - y * t.x;}
    bool operator <(pt t){return x == t.x ? y < t.y : x < t.x;}
    ll sz(){return x * x + y * y;}
};

int ccw(pt a, pt b, pt c){
    b = b - a; c = c - a;
    ll t = b / c;
    return (t < 0) - (t > 0);
}

vector<int> hull(vector<pt> arr){
    int a, b, ix = min_element(all(arr)) - arr.begin();
    vector<int> v, st{ix};
    for(int i = 0; i < arr.size(); i++) if(i != ix) v.emplace_back(i);
    
    sort(all(v), [&](int a, int b){
        pt x = arr[a] - arr[ix], y = arr[b] - arr[ix];
        return x / y ? x / y > 0 : x.sz() < y.sz();
    });
    
    for(int& i : v){
        while(st.size() > 1 && ccw(arr[st[st.size() - 2]], arr[st.back()], arr[i]) < 0) st.pop_back();
        st.emplace_back(i);
    }
    return st;
}

double area(vector<pt> v){
    double ret = 0;
    for(int i = 0, n = v.size(); i < n; i++)
        ret += v[i] / v[(i + 1) % n];
    return abs(ret) / 2.0; 
}


ll n;
int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n;
    vector<pt> v(n), arr;
    vector<int> tmp;
    for(int i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    tmp = hull(v);
    cout << tmp.size() << '\n';
    for(int& ix : tmp) arr.emplace_back(v[ix]);
    cout << area(arr);
    return 0;
}
