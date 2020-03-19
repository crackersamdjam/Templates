#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
using ll = long long;

ll mulmod(ll a, ll b, ll mod){
    ll res = 0;
    a = a % mod;
    while(b > 0){
        if(b % 2 == 1)
            res = (res + a) % mod;
        
        a = (a * 2) % mod;
        
        b /= 2;
    }
    return res % mod;
}

//only works with this mod
constexpr ll mod61 = (1ull<<61) - 1;
ll modmul(ll a, ll b){
    a %= mod61, b %= mod61;
    ll l1 = (int)a, h1 = a>>32, l2 = (int)b, h2 = b>>32;
    ll l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    ll ret = (l&mod61) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod61) + (ret>>61);
    ret = (ret & mod61) + (ret>>61);
    return ret-1;
}

int main(){
    ll a, b, m;
    //cin>>a>>b>>m;
    a = 9223372036854775807;
    b = 9223372036854775807;
    //m = 100000000000;
    m = (1LL<<61)-1;
    __int128 c = a, d = b;
    print(mulmod(a, b, m), modmul(a, b), a*b%m, c*d%m);
    
    
    return 0;
}
/*
9223372036854775807
9223372036854775807
100000000000
 */