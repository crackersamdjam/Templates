#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
const int MM = 55;
using ld = double;

int n;
double x[MM], y[MM], ans = 1e16;

double dis(double x1, double y1, double x2, double y2){
    return sqrtl((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
void check(double cx, double cy){
    double mx = 0;
    for(int i=0; i<n; i++)
        mx = max(mx, dis(x[i], y[i], cx, cy));
    ans = min(ans, mx);
    //cout << cx << ' ' << cy << ' ' << mx << '\n';
}
//centroid of three points
void cent(int a, int b, int c){
    ld a1 = x[b]-x[a], b1 = y[b]-y[a], c1 = (a1*a1 + b1*b1)/2;
    ld a2 = x[c]-x[a], b2 = y[c]-y[a], c2 = (a2*a2 + b2*b2)/2;
    ld d = a1*b2 - a2*b1;
    //watch out for infinate coordinates
    if(d != 0)
        check(x[a] + (c1*b2 - c2*b1)/d, y[a] + (a1*c2 - a2*c1)/d);
}

//two centers of circle where two points are on it if radius is 2.5
void solve(int a, int b){
    double mx = (x[a] + x[b])/2, my = (y[a] + y[b])/2, m = 0.0;
    if(x[a] != x[b]) m = -(x[a] - x[b])/(y[a]-y[b]);
    double d = sqrt(6.25 - dis(x[a], y[a], mx, my));
    double dx = d / sqrt(1+m*m), dy = d*m/sqrt(1+m*m);
    check(mx-dx, my-dy); check(mx+dx, my+dy);
}