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
const int MM = 1e5+1;

mt19937 g1(time(0));
int randint(int a, int b){return uniform_int_distribution<int>(a, b)(g1);}

int n;
vector<int> adj[MM];

// generates a random tree with n vertices (Prufer Sequence)
vector<pair<int, int>> init(){
    vector<int> code(n-2);
    for(int &i: code)
        i = randint(0, n-1);
    
    vector<int> degree(n, 1);
    for(int i : code)
        degree[i]++;
    
    int ptr = 0;
    while(degree[ptr] != 1)
        ptr++;
    int leaf = ptr;
    
    vector<pair<int, int>> edges;
    for(int v : code){
        edges.emplace_back(leaf, v);
        if(--degree[v] == 1 && v < ptr){
            leaf = v;
        }
        else{
            ptr++;
            while(degree[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
    edges.emplace_back(leaf, n-1);
    return edges;
}


int main(){
    
    n = 10;
    print(n);
    
    puts("-------------");
    
    vector<pair<int, int>> edges = init();
    for(auto &e: edges){
        e.first++, e.second++;
        print(e.first, e.second);
        adj[e.first].emplace_back(e.second);
        adj[e.second].emplace_back(e.first);
    }
    
    puts("-------------");
    
    
    return 0;
}
