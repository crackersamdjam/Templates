#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
const int MM = 1001 ;

int N, M, dis[MM];
bool vis[MM];
vector<pair<int, int>> adj[MM];

int main(){
    
    scan(N, M);
    
    for(int i = 0,a,b,c; i < M; i++){
        scan(a, b, c);
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    
    memset(dis, 0x3f, sizeof dis);
    
    dis[1] = 0;
    
    for(int i = 0; i < N; i++){
        int edge = INT_MAX, next = -1;
        for(int j = 1; j <= N; j++){
            if(dis[j] < edge && !vis[j]){
                edge = dis[j];
                next = j;
            }
        }
        if(next == -1)
            break;
        vis[next] = 1;
        for(auto e: adj[next]){
            if(dis[next] + e.second < dis[e.first]){
                dis[e.first] = dis[next] + e.second;
            }
        }
    }
    
    for(int i = 1; i <= N; i++){
        print(dis[i] == 0x3f3f3f3f? -1: dis[i]);
    }
    
    return 0;
}
