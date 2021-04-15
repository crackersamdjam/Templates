using ll = long long;
using T = ll;
using L = ll;
constexpr int MM = 5e5+5;
extern int n;

struct Segtree{
	#define lc rt<<1
	#define rc rt<<1|1
	#define nm ((nl+nr)/2)
	#define npm int nl = 0, int nr = n, int rt = 1
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
	} tree[MM*4];
	
	const T DEF = 0; const L DEFL = 0;
	
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
	
	void point_update(int i, L x, npm){
		if(nl == nr){
			tree[rt].apply(x);
			return;
		}
		push(rt, nl, nr);
		i <= nm ? point_update(i, x, lpm) : point_update(i, x, rpm);
		pull(rt);
	}
	
	T query(int l, int r, npm){
		if(r < nl or nr < l) return DEF;
		if(l <= nl and nr <= r)
			return tree[rt].val;
		push(rt, nl, nr);
		return merge(query(l, r, lpm), query(l, r, rpm));
	}
	
	// upper_bound (first point of failure)
	int kth(int k, npm){
		if(nl == nr)
			return nl;
		push(rt, nl, nr);
		return k < tree[lc].val ? kth(k, lpm) : kth(k-tree[lc].val, rpm);
	}

	#undef lc
	#undef rc
	#undef nm
	#undef npm
	#undef lpm
	#undef rpm
};