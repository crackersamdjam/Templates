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
const int MM = 2e5+2;

#define sq(x) (x)*(x)

int n, q[MM], l, r;
ll c, dp[MM], a[MM];

long double eval(int k, int j){
    return 1.0*(dp[j] - dp[k] + sq(a[j]) - sq(a[k]))/(a[j]-a[k]);
}

int main(){
    scan(n, c, a[0]);
    
    for(int i = 1; i < n; i++){
        scan(a[i]);
        while(l < r and 2*a[i] >= eval(q[l], q[l+1]))
            l++;
        
        dp[i] = dp[q[l]] + sq(a[i]-a[q[l]]) + c;
        
        while(l < r and eval(q[r-1], q[r]) >= eval(q[r], i))
            r--;
        
        q[++r] = i;
    }
    
    print(dp[n-1]);
    
    return 0;
}
/*
dp[i] = dp[j] + (a[i]-a[j])^2 + c

dp[k] + (a[i]-a[k])^2 <= dp[j] + (a[i]-a[j])^2
dp[k] + a[i]^2 - 2a[i]a[k] + a[k]^2 <= dp[j] + a[i]^2 -2a[i]a[j] + a[j]^2
2a[i]a[j] - 2a[i]a[k] <= dp[j] - dp[k] + a[j]^2 - a[k]^2
2a[i](a[j]-a[k]) <= dp[j] - dp[k] + a[j]^2 - a[k]^2
2a[i] <= (dp[j] - dp[k] + a[j]^2 - a[k]^2) / (a[j]-a[k])

a[j] - a[k] always positive

 wait I messed up switch every <= to >= (the comment lines above)
 
 
 */