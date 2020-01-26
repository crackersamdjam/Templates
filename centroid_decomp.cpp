#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;register bool _=0;register T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){register bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MM = 1e5+1;

int n, tot, sz[MM];
vector<pii> adj[MM];
bool vis[MM];

int getsz(int cur, int pre){
    sz[cur] = 1;
    for(auto e: adj[cur]){
        int u = e.first;
        if(u != pre && !vis[u])
            sz[cur] += getsz(u, cur);
    }
    return sz[cur];
}

int findcent(int cur, int pre){
    for(auto e: adj[cur]){
        int u = e.first;
        if(!vis[u] && u != pre && sz[u]*2 > tot)
            return findcent(u, cur);
    }
    return cur;
}

void dfs1(int cur, int pre){
    
    for(auto u: adj[cur]){
        if(u.first == pre || vis[u.first])
            continue;
        
        // do stuff
        
        dfs1(u.first, cur);
    }
}


void go(int root){
    
    getsz(root, -1);
    tot = sz[root];
    if(tot == 1)
        return;
    int cent = findcent(root, -1);
    vis[cent] = 1;
    
    dfs1(cent, 0);
    
    // process paths
    
    for(auto u: adj[cent]){
        if(vis[u.first])
            continue;
        
        // subtract overcount for each subtree (if necessary)
    }
    
    for(auto u: adj[cent]){
        if(!vis[u.first])
            go(u.first);
    }
}


int main(){
    
    
    
    return 0;
}
