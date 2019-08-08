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
const int MM = 4e5+1, MN = 1e5+1;

#define lc (rt<<1)
#define rc (rt<<1|1)
#define nm ((nl+nr)>>1)

struct node{
    int val, lp;
} tree[MM*3];

inline void push_up(int rt){
    tree[rt].val = max(tree[lc].val, tree[rc].val);
}

// node with lazy val means yet to push to children (but updated itself)
inline void push_down(int rt, int nl, int nr){
    int &val = tree[rt].lp;
    if(val && nl^nr){
        tree[lc].lp += val;
        tree[lc].val += val;
        tree[rc].lp += val;
        tree[rc].val += val;
    }
    val = 0;
}

void build(int l, int r, int rt = 1){
    int nl = l, nr = r;
    if(l == r){
        tree[rt].val = 0;
        return;
    }
    build(l, nm, lc);
    build(nm+1, r, rc);
    push_up(rt);
}

void update(int l, int r, int val, int nl = 1, int nr = MM-1, int rt = 1){
    if(r < nl || l > nr)
        return;
    if(l <= nl && r >= nr){
        tree[rt].val += val;
        tree[rt].lp += val;
        return;
    }
    push_down(rt, nl, nr);
    update(l, r, val, nl, nm, lc);
    update(l, r, val, nm+1, nr, rc);
    push_up(rt);
}

int query(int l, int r, int nl = 1, int nr = MM-1, int rt = 1){
    if(r < nl || l > nr)
        return 0;
    if(l <= nl && r >= nr)
        return tree[rt].val;
    push_down(rt, nl, nr);
    return max(query(l, r, nl, nm, lc), query(l, r, nm+1, nr, rc));
}

int main(){
    
    
    return 0;
}