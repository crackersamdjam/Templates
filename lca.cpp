#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;register bool _=0;register T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){register bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
const int MM = 1e5+1, MN = 25;

int n, dep[MM], lca[MN][MM], val[MN][MM];

int getlca(int u, int v){
    if(dep[u] < dep[v])
        swap(u, v);
    //u gets jumped up
    for(int i = MN-1; i >= 0; i--){
        if((lca[i][u] != -1) && (dep[lca[i][u]] >= dep[v]))
            u = lca[i][u];
    }
    //now should be on same level
    if(u == v)
        return u;
    for(int i = MN-1; i >= 0; i--){
        if((lca[i][u] != -1) && (lca[i][v] != -1) && (lca[i][u] != lca[i][v])){
            u = lca[i][u];
            v = lca[i][v];
        }
    }
    return lca[0][u];
    //return direct parent
}

//binary lift

int query(int a, int b){
    
    int lcan = getlca(a, b), ret = 0;
    
    for(int i = MN-1; i >= 0; i--){
        if(dep[a] >= dep[lcan] + (1<<i)){
            ret = max(ret, val[i][a]);
            a = lca[i][a];
        }
    }
    
    for(int i = MN-1; i >= 0; i--){
        if(dep[b] >= dep[lcan] + (1<<i)){
            ret = max(ret, val[i][b]);
            b = lca[i][b];
        }
    }
    return ret;
}

int main(){
    
    memset(lca, -1, sizeof lca);
    
    //dfs
    
    for(int i = 1; i < MN; i++){
        for(int j = 0; j <= n; j++){
            if(~lca[i-1][j]){
                lca[i][j] = lca[i-1][ lca[i-1][j] ];
                val[i][j] = max(val[i-1][j], val[i-1][ lca[i-1][j] ]);
            }
        }
    }
    
    return 0;
}
