#pragma once
#include <bits/stdc++.h>

using namespace std;

template<class T, class L> struct Segtree{
	#define lc rt<<1
	#define rc rt<<1|1
	#define nm ((nl+nr)/2)
	#define dpm LS, RS, 1
	#define npm int nl, int nr, int rt
	#define lpm nl, nm, lc
	#define rpm nm+1, nr, rc
	
	struct node{
		T val; L lp;
		int sz;
		inline void apply(L v){
			val += v*sz; // range sum
			//val += v;
			lp += v;
		}
	};
	
	vector<node> tree;
	const T DEF = 0;
	const L DEFL = 0;
	int LS, RS;
	
	T merge(T va, T vb){
		return va+vb;
	}
	
	void pull(int rt){
		tree[rt].val = merge(tree[lc].val, tree[rc].val);
	}
	
	void push(int rt, int nl, int nr){
		// node with lazy val means yet to push to children (but updated itself)
		if(nl == nr or tree[rt].lp == DEFL) return;
		L &x = tree[rt].lp; tree[lc].apply(x); tree[rc].apply(x); x = DEFL;
	}
	
	void build(npm){
		tree[rt].val = DEF;
		tree[rt].lp = DEFL;
		tree[rt].sz = nr-nl+1;
		if(nl == nr) return;
		build(lpm); build(rpm);
	}
	
	void init(int l, int r){
		tree.resize((r-l+1)*4+5);
		LS = l, RS = r;
		build(dpm);
	}
	
	void update(int l, int r, L x){ update(l, r, x, dpm); }
	void update(int l, int r, L x, npm){
		if(r < nl or nr < l) return;
		if(l <= nl and nr <= r){
			tree[rt].apply(x);
			return;
		}
		push(rt, nl, nr);
		update(l, r, x, lpm); update(l, r, x, rpm);
		pull(rt);
	}
	
	void point_update(int i, L x){ point_update(i, x, dpm); }
	void point_update(int i, L x, npm){
		if(nl == nr){
			tree[rt].apply(x);
			return;
		}
		push(rt, nl, nr);
		i <= nm ? point_update(i, x, lpm) : point_update(i, x, rpm);
		pull(rt);
	}
	
	T query(int l, int r){ return query(l, r, dpm); }
	T query(int l, int r, npm){
		if(r < nl or nr < l) return DEF;
		if(l <= nl and nr <= r)
			return tree[rt].val;
		push(rt, nl, nr);
		return merge(query(l, r, lpm), query(l, r, rpm));
	}
	
	// upper_bound (first point of failure)
	T sub(T a, T b){
		return a-b;
	}
	int kth(int k){ return kth(k, dpm); }
	int kth(int k, npm){
		if(nl == nr)
			return nl;
		push(rt, nl, nr);
		return k < tree[lc].val ? kth(k, lpm) : kth(sub(k, tree[lc].val), rpm);
	}
	
	#undef lc
	#undef rc
	#undef nm
	#undef dpm
	#undef npm
	#undef lpm
	#undef rpm
};