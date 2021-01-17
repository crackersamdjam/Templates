// https://dmoj.ca/problem/lazy
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define gc getchar()
#define pc(x) putchar(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

#define lc (rt<<1)
#define rc (rt<<1|1)
#define nm ((nl+nr)>>1)

using namespace std;
using ll = long long;
const int MM = 4e5+5;

struct Combine{
	using T = ll;
	using L = pair<ll, ll>;
	const T def = LLONG_MAX;
	const L ldef = make_pair(LLONG_MAX, 0);
	T merge(const T &l, const T &r) const{ return min(l, r); }
	T applyL(const T &l, const L &r) const{ return r.first != LLONG_MAX ? r.first : l + r.second; }
	L getSegmentVal(const L &v, int k) const{ return v; }
	L mergeL(const L &l, const L &r) const{
		if (r.first != LLONG_MAX) return r;
		if (l.first != LLONG_MAX) return make_pair(l.first + r.second, 0);
		return make_pair(LLONG_MAX, l.second + r.second);
	}
};

template<class Combine> struct segtree{
	using T = typename Combine::T; using L = typename Combine::L;
	Combine cc; int n; vector<T> t; vector<L> lp;
	
	void apply(const L &v, int nl, int nr, int rt){
		t[rt] = cc.applyL(t[rt], cc.getSegmentVal(v, nr-nl+1));
		lp[rt] = cc.mergeL(lp[rt], v);
	}
	void push(int nl, int nr, int rt){
		if(nl == nr || lp[rt] == cc.ldef) return;
		apply(lp[rt], nl, nm, lc); apply(lp[rt], nm+1, nr, rc); lp[rt] = cc.ldef;
	}
	void build( int nl, int nr, int rt){
		if(nl == nr){
			t[rt] = 0;
			return;
		}
		build(nl, nm, lc); build(nm+1, nr, rc); t[rt] = cc.merge(t[lc], t[rc]);
	}
	void update(int l, int r, const L &v, int nl, int nr, int rt){
		if(r < nl || l > nr)
			return;
		if(l <= nl and nr <= r){
			apply(v, nl, nr, rt);
			return;
		}
		push(nl, nr, rt);
		update(l, r, v, nl, nm, lc); update(l, r, v, nm+1, nr, rc); t[rt] = cc.merge(t[lc], t[rc]);
	}
	T query(int l, int r, int nl, int nr, int rt){
		if(r < nl || nr < l)
			return cc.def;
		if(l <= nl && nr <= r)
			return t[rt];
		push(nl, nr, rt);
		return cc.merge(query(l, r, nl, nm, lc), query(l, r, nm+1, nr, rc));
	}
	void update(int l, int r, const L &v){ update(l, r, v, 0, n-1, 1); }
	void update(int i, const L &v){ update(i, i, v, 0, n-1, 1); }
	T query(int l, int r){ return query(l, r, 0, n-1, 1); }
	segtree(int n): n(n), t(max(0, 4*n), cc.def){
		if(n > 0){
			lp.assign(4*n, cc.ldef);
			build(0, n-1, 1);
		}
	}
};

int n, q, a[MM];

int main(){
	
	scan(n, q);
	segtree<Combine> ST(n+1);
	for(int i = 1; i <= n; i++){
		scan(a[i]);
		ST.update(i, {LLONG_MAX, a[i]});
	}
	
	for(int t = 0,op,l,r,v; t < q; t++){
//		for(int i = 1; i <= n; i++)
//			cout<<ST.query(i, i)<<' ';
		
		scan(op, l, r);
		if(op == 1){
			scan(v);
			ST.update(l, r, make_pair(LLONG_MAX, v));
		}
		else if(op == 2){
			scan(v);
			ST.update(l, r, make_pair(v, 0));
		}
		else{
			print(ST.query(l, r));
		}
	}
}