#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

#define lc (rt<<1)
#define rc (rt<<1|1)
#define nm ((nl+nr)>>1)

using namespace std;
using T = long long;
using L = long long;
const int MM = 4e5+5;

struct node{
	T val; L lp; int sz;
	inline void apply(L v){
		// val += v*sz; range sum
		val += v;
		lp += v;
	}
};

struct segtree{
	node tree[MM*4];
	const T DEF = 0;
	const L DEFL = 0;
	int LS, RS;
	
	inline T merge(T va, T vb){
		return max(va, vb);
	}
	
	inline void pull(int rt){
		tree[rt].val = merge(tree[lc].val, tree[rc].val);
	}
	
	inline void push(int rt, int nl, int nr){ // node with lazy val means yet to push to children (but updated itself)
		if(nl == nr or tree[rt].lp == DEFL) return;
		L &val = tree[rt].lp; tree[lc].apply(val); tree[rc].apply(val); val = DEFL;
	}
	
	void build(int _LS, int _RS){ build(LS = _LS, RS = _RS, 1); }
	void build(int nl, int nr, int rt){
		tree[rt].val = DEF;
		tree[rt].lp = DEFL;
		tree[rt].sz = nr-nl+1;
		if(nl == nr) return; build(nl, nm, lc); build(nm+1, nr, rc); pull(rt);
	}
	
	void update(int l, int r, L val){ update(l, r, val, LS, RS, 1); }
	void update(int l, int r, L val, int nl, int nr, int rt){
		if(r < nl || l > nr) return;
		if(l <= nl && r >= nr){
			tree[rt].apply(val);
			return;
		}
		push(rt, nl, nr); update(l, r, val, nl, nm, lc); update(l, r, val, nm+1, nr, rc); pull(rt);
	}
	
	T query(int l, int r){ return query(l, r, LS, RS, 1); }
	T query(int l, int r, int nl, int nr, int rt){
		if(r < nl || l > nr) return DEF;
		if(l <= nl && r >= nr) return tree[rt].val;
		push(rt, nl, nr); return merge(query(l, r, nl, nm, lc), query(l, r, nm+1, nr, rc));
	}
	
	// upper_bound (first point of failure)
	// change k-tree[lc].val to whatever is needed
	// int kth(int k){ return kth(k, LS, RS, 1);}
	// int kth(int k, int nl, int nr, int rt){
	// 	if(nl == nr)
	// 		return nl;
	// 	push(rt, nl, nr);
	// 	if(k < tree[lc].val)
	// 		return kth(k, nl, nm, lc);
	// 	return kth(k-tree[lc].val, nm+1, nr, rc);
	// }
} ST;


int main(){
	ST.build(0, 5);
	ST.update(1, 2, 4);
	ST.update(2, 5, 1);
	print(ST.query(2, 3));
}
