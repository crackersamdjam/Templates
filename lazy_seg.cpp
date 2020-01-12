#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;register bool _=0;register T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){register bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
using T = long long;
const int MM = 4e5+2;

#define lc (rt<<1)
#define rc (rt<<1|1)
#define nm ((nl+nr)>>1)

struct node{
    T val, lp;
    bool up;
    void apply(T v){
        val += v;
        lp += v;
        up = 1;
    }
};

struct segtree{
    
    node tree[MM*3];
    T DEF = 0;
    //default value
    
    T merge(T va, T vb){
        return max(va, vb);
    }
    
    void push_up(int rt){
        tree[rt].val = merge(tree[lc].val, tree[rc].val);
    }
    
    // node with lazy val means yet to push to children (but updated itself)
    void push_down(int rt, int nl, int nr){
        T &val = tree[rt].lp;
        if(tree[rt].up && nl != nr){
            tree[lc].apply(val);
            tree[rc].apply(val);
        }
        val = DEF;
        tree[rt].up = 0;
    }
    
    void build(int l = 1, int r = MM-1, int rt = 1){
        int nl = l, nr = r;
        if(l == r){
            tree[rt].val = DEF;
            tree[rt].lp = 0;
            tree[rt].up = 0;
            return;
        }
        build(l, nm, lc);
        build(nm+1, r, rc);
        push_up(rt);
    }
    
    void update(int l, int r, T val, int nl = 1, int nr = MM-1, int rt = 1){
        if(r < nl || l > nr)
            return;
        if(l <= nl && r >= nr){
            tree[rt].apply(val);
            return;
        }
        push_down(rt, nl, nr);
        update(l, r, val, nl, nm, lc);
        update(l, r, val, nm+1, nr, rc);
        push_up(rt);
    }
    
    T query(int l, int r, int nl = 1, int nr = MM-1, int rt = 1){
        if(r < nl || l > nr)
            return DEF;
        if(l <= nl && r >= nr)
            return tree[rt].val;
        push_down(rt, nl, nr);
        return merge(query(l, r, nl, nm, lc), query(l, r, nm+1, nr, rc));
    }
} t;

int main(){
    
    t.build();
    t.update(1, 2, 4);
    t.update(2, 5, 1);
    print(t.query(2, 3));
    
    return 0;
}