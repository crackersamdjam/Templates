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
const int MAXLEN = 1e6+2, N = 1;

ll base[] = {131};
ll mod[] = {(ll)1e9+7};

int flog(ll x){
    return 63-__builtin_clz(x);
}
ll gcd(ll gcd_a, ll gcd_b){return gcd_b == 0 ? gcd_a : gcd(gcd_b, gcd_a % gcd_b);}
ll fpow(ll fpow_b, ll fpow_exp, ll fpow_mod){if(fpow_exp == 0) return 1;ll t = fpow(fpow_b,fpow_exp/2,fpow_mod);if(fpow_exp&1) return t*t%fpow_mod*fpow_b%fpow_mod;return t*t%fpow_mod;}
ll divmod(ll divmod_i, ll divmod_j, ll divmod_mod){divmod_i%=divmod_mod,divmod_j%=divmod_mod;return divmod_i*fpow(divmod_j,divmod_mod-2,divmod_mod)%divmod_mod;}

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<ll, string> mp;

string a[N], b[N];
ll val[N];
bool done;

void go(int j, int i, ll h, string &s){
    if(done)
        return;
    if(!i){
        if(mp[h].size()){
            a[j] = mp[h];
            b[j] = s;
            val[j] = h;
            done = 1;
        }
        mp[h] = s;
        return;
    }
    if(j == 0){
        for(int c = 'a'; c <= 'z'; c++){
            s.push_back(c);
            go(j, i+1, (h*base[j]+c)%mod[j], s);
            s.pop_back();
        }
    }
    else{
        s.push_back(0);
        go(j, i+1, (h*base[j])%mod[j], s);
        s.pop_back();
        //fix
    }
}

int main(){
    
    for(int i = 0; i < N; i++){
        ll sq = sqrtl(mod[i]);
        int m = log2(sq)/log2(26)+2;
        m = min(m, MAXLEN);
        print(fpow(26, m, 1e16), sq);
        
        do{
            mp.clear();
            done = 0;
            string def;
            go(i, 0, m, def);
            
        } while(!done);
    }
    
    return 0;
}
/*
 * unfinished
 * before recurse, make previous alphabet and what it's hash will be
 */