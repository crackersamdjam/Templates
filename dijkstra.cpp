#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
using pii = pair<int, int>;
const int MM = 1;

vector<pii> adj[MM];
priority_queue<pii, vector<pii>, greater<pii>> q;
int dis[MM], pre[MM];

int main(){
    
    
    
    while(!q.empty()){
        int d = q.top().first; int u = q.top().second; q.pop();
        if(d > dis[u]) continue;
        for(auto e: adj[u]){
            if(dis[u] + e.second < dis[e.first]){
                pre[e.first] = u;
                q.push({dis[e.first] = dis[u] + e.second, e.first});
            }
        }
    }
    
    return 0;
}