// https://atcoder.jp/contests/dp/tasks/dp_z

#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
using ll = long long;
const int MM = 2e5+2, MN = 1e6+2;

int n;
ll c, dp[MM], a[MM];

#define sq(x) (x)*(x)

struct line{
    ll m, b;
    ll f(ll x){
        return m*x + b;
    }
} tree[MN*4];

void add(line ln, int l = 0, int r = MN-1, int rt = 1){
    int m = (l+r)/2;
    bool bl = ln.f(l) < tree[rt].f(l);
    bool bm = ln.f(m) < tree[rt].f(m);
    if(bm)
        swap(tree[rt], ln);
    if(l == r)
        return;
    if(bl != bm)
        add(ln, l, m, rt<<1);
    else
        add(ln, m+1, r, rt<<1|1);
}

ll get(int x, int l = 0, int r = MN-1, int rt = 1){
    int m = (l+r)/2;
    if(l == r)
        return tree[rt].f(x);
    if(x <= m)
        return min(tree[rt].f(x), get(x, l, m, rt<<1));
    return min(tree[rt].f(x), get(x, m+1, r, rt<<1|1));
}

int main(){
    scan(n, c, a[1]);
    add({-2*a[1], a[1]*a[1]});
    
    for(int i = 2; i <= n; i++){
        scan(a[i]);
        dp[i] = get(a[i]) + a[i]*a[i] + c;
        add({-2*a[i], dp[i] + a[i]*a[i]});
    }
    
    print(dp[n]);
    
    return 0;
}
/*
dp[i] = dp[j] + (a[i]-a[j])^2 + c

dp[k] + (a[i]-a[k])^2 <= dp[j] + (a[i]-a[j])^2
dp[k] + a[i]^2 - 2a[i]a[k] + a[k]^2 <= dp[j] + a[i]^2 -2a[i]a[j] + a[j]^2
2a[i]a[j] - 2a[i]a[k] <= dp[j] - dp[k] + a[j]^2 - a[k]^2
2a[i](a[j]-a[k]) <= dp[j] - dp[k] + a[j]^2 - a[k]^2
2a[i] <= (dp[j] - dp[k] + a[j]^2 - a[k]^2) / (a[j]-a[k])
 be careful not to divide by negative
 
 or just li chao
 y = mx + b
 b = dp[j] + a[j]^2 (+ a[i]^2 + c)
 m = -2a[j]
 x becomes a[i]
 
 */
