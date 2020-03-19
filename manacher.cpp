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
const int MM = 50008;

int n, r[MM];
char s[MM];

int main(){
    
    scanf("%d %s", &n, s+1);
    
    int m = n*2+1;
    
    for(int i = m; i; i--){
        if(i&1)
            s[i] = s[i>>1];
        else
            s[i] = '#';
    }
    s[1] = '@'; //stop from exending beyond
    s[m+1] = '#';
    
    for(int i = 1, mx = 0, p = 0; i <= m; i++){
        //cout<<i<<' '<<s[i]<<'\n';
        if(i >= mx)
            r[i] = 1;
        else
            r[i] = min(mx-i, r[p*2-i]);
        
        //p*2 = leftend + rightend
        //leftend + rightend-i reflects i across p
        
        while(s[i-r[i]] == s[i+r[i]])
            r[i]++;
        if(i + r[i] > mx)
            mx = i + r[i], p = i;
    }
    
    int* st = max_element(r+1, r+n*2+1), ans = 0;
    
    for(int i = st-r-*st+1; i < st-r+*st; i++){
        if(i%2)
            pc(s[i]), ans++;
    }
    
    pc(10);
    
    print(ans);
    assert(ans == *st-1);
    
    return 0;
}