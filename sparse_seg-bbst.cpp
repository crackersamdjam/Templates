// IOI '13 P6 - Game

#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;register bool _=0;register T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){register bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

typedef long long ll;

std::mt19937 gen(time(0));
std::uniform_int_distribution<int> dis;

namespace treap{
    
    struct tnode{
        int key, pr;
        ll val, gcd;
        tnode *l, *r;
        tnode(int key, ll val){
            this->key = key;
            this->val = this->gcd = val;
            pr = dis(gen);
        }
    };
    
    inline void upd(tnode *rt){
        if(rt)
            rt->gcd = std::__gcd(rt->l ? rt->l->gcd : 0, std::__gcd(rt->val, rt->r ? rt->r->gcd : 0));
    }
    
    void split(tnode *cur, int key, tnode *&l, tnode *&r){
        if(!cur){
            l = r = nullptr;
            return;
        }
        if(cur->key > key){
            split(cur->l, key, l, cur->l);
            r = cur;
        }
        else{
            split(cur->r, key, cur->r, r);
            l = cur;
        }
        upd(cur);
    }
    
    void merge(tnode *&cur, tnode *l, tnode *r){
        if(!l || !r)
            cur = l ? l : r;
        else if(l->pr > r->pr){
            merge(l->r, l->r, r);
            cur = l;
        }
        else{
            merge(r->l, l, r->l);
            cur = r;
        }
        upd(cur);
    }
    
    void insert(tnode *&cur, tnode *tnode, bool russian){
        if(!cur)
            cur = tnode;
        else if(cur->key == tnode->key)
            cur->val = tnode->val;
        else if(!russian && cur->pr > tnode->pr){
            split(cur, tnode->key, tnode->l, tnode->r);
            cur = tnode;
        }
        else
            insert(tnode->key < cur->key ? cur->l : cur->r, tnode, russian);
        upd(cur->l);
        upd(cur->r);
        upd(cur);
    }
    
    bool exist(tnode *cur, int k){
        if(!cur)
            return 0;
        if(cur->key == k)
            return 1;
        if(cur->key > k)
            return exist(cur->l, k);
        return exist(cur->r, k);
    }
    
    ll index(tnode *cur, int k){
        if(!cur)
            return 0;
        if(cur->key == k)
            return cur->val;
        if(cur->key > k)
            return index(cur->l, k);
        return index(cur->r, k);
    }
}

struct node{
    node *l, *r;
    treap::tnode *rt;
    
    void update(int nl, int nr, int i, int j, ll v){
        if(nl == nr){
            insert(rt, new treap::tnode(j, v), exist(rt, j));
            return;
        }
        int nm = (nl+nr)/2;
        if(i <= nm){
            if(!l) l = new node();
            l->update(nl, nm, i, j, v);
        }
        else{
            if(!r) r = new node();
            r->update(nm+1, nr, i, j, v);
        }
        if(rt) insert(rt, new treap::tnode(j, std::__gcd(l ? index(l->rt, j) : 0, r ? index(r->rt, j) : 0)), exist(rt, j));
        else insert(rt, new treap::tnode(j, v), 0);
    }
    
    ll query(int nl, int nr, int lx, int rx, int ly, int ry){
        if(rx < nl || lx > nr)
            return 0;
        if(lx <= nl && nr <= rx){
            treap::tnode *a, *b, *c;
            treap::split(rt, ly-1, a, b);
            treap::split(b, ry, b, c);
            ll ret = b ? b->gcd : 0;
            merge(b, b, c);
            merge(rt, a, b);
            return ret;
        }
        int nm = (nl+nr)/2;
        return std::__gcd(l? l->query(nl, nm, lx, rx, ly, ry) : 0, r? r->query(nm+1, nr, lx, rx, ly, ry) : 0);
    }
    
} segrt;

int n, m;

void init(int r, int c){
    n = r, m = c;
}

void update(int i, int j, ll k){
    segrt.update(0, n-1, i, j, k);
}

ll calculate(int lx, int ly, int rx, int ry){
    return segrt.query(0, n-1, lx, rx, ly, ry);
}