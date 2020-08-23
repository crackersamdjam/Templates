#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define gc getchar()
#define pc(x) putchar(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=char(n%10+48);n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
using ll = long long;
const int MM = 1e5+5;

//// Below is a sample struct for range assignment and range sum queries
//struct Combine{
//	using Data = int;
//	using Lazy = int;
//	const Data qdef = 0;
//	const Lazy ldef = INT_MIN;
//	Data merge(const Data &l, const Data &r) const { return l + r; }
//	Data applyLazy(const Data &l, const Lazy &r) const { return r; }
//	Lazy getSegmentVal(const Lazy &v, int k) const { return v * k; }
//	Lazy mergeLazy(const Lazy &l, const Lazy &r) const { return r; }
//};

struct Combine{
	using Data = ll;
	using Lazy = pair<ll, ll>;
	const Data qdef = LLONG_MAX;
	const Lazy ldef = make_pair(LLONG_MAX, 0);
	Data merge(const Data &l, const Data &r) const{ return min(l, r); }
	Data applyLazy(const Data &l, const Lazy &r) const{ return r.first != LLONG_MAX ? r.first : l + r.second; }
	Lazy getSegmentVal(const Lazy &v, int k) const{ return v; }
	Lazy mergeLazy(const Lazy &l, const Lazy &r) const{
		if (r.first != LLONG_MAX) return r;
		if (l.first != LLONG_MAX) return make_pair(l.first + r.second, 0);
		return make_pair(LLONG_MAX, l.second + r.second);
	}
};

template<class Combine> struct segtree{
#define nm ((nl+nr)>>1)
#define lc (rt+1)
#define rc (rt+(nm-nl+1)*2)
	using Data = typename Combine::Data; using Lazy = typename Combine::Lazy;
	Combine C; int n; vector<Data> t; vector<Lazy> lp;
	
	void apply(const Lazy &v, int nl, int nr, int rt){
		t[rt] = C.applyLazy(t[rt], C.getSegmentVal(v, nr-nl+1));
		lp[rt] = C.mergeLazy(lp[rt], v);
	}
	void push(int nl, int nr, int rt){
		if(nl == nr || lp[rt] == C.ldef) return;
		apply(lp[rt], nl, nm, lc); apply(lp[rt], nm+1, nr, rc); lp[rt] = C.ldef;
	}
	
	template<class F> void build(F &f, int nl, int nr, int rt){
		if(nl == nr){
			t[rt] = f();
			return;
		}
		build(f, nl, nm, lc); build(f, nm+1, nr, rc); t[rt] = C.merge(t[lc], t[rc]);
	}
	void update(int l, int r, const Lazy &v, int nl, int nr, int rt){
		if(r < nl || l > nr)
			return;
		if(l <= nl and nr <= r){
			apply(v, nl, nr, rt);
			return;
		}
		push(nl, nr, rt);
		update(l, r, v, nl, nm, lc); update(l, r, v, nm+1, nr, rc); t[rt] = C.merge(t[lc], t[rc]);
	}
	Data query(int l, int r, int nl, int nr, int rt){
		if(r < nl || nr < l)
			return C.qdef;
		if(l <= nl && nr <= r)
			return t[rt];
		push(nl, nr, rt);
		return C.merge(query(l, r, nl, nm, lc), query(l, r, nm+1, nr, rc));
	}
	template<class F> segtree(int n, F f): n(n), t(max(0, 2*n), C.qdef){
		if(n > 0){
			lp.assign(2*n, C.ldef);
			build(f, 0, n-1, 1);
		}
	}
	template<class It> segtree(It st, It en): segtree(en-st, [&]{ return *st++; }){}
	segtree(int n, const Data &vdef): segtree(n, [&]{ return vdef; }){}
	void update(int l, int r, const Lazy &v){ update(l, r, v, 0, n-1, 1); }
	void update(int i, const Lazy &v){ update(i, i, v, 0, n-1, 1); }
	Data query(int l, int r){ return query(l, r, 0, n-1, 1); }
};

int n, q, a[MM];

int main(){
	
	scan(n, q);
	segtree<Combine> ST(n+1, 0LL);
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
//int main(){
//	segtree<Combine> ST(7, 0);
//	ST.update(1, 3, 2);
//	print(ST.query(3, 4));
//	ST.update(3, 5, 1);
//	print(ST.query(2, 5));
//
//	for(int i = 0; i < 6; i++)
//		cout<<ST.query(i, i)<<' ';
//	cout<<endl;
//	for(int i = 0; i < 6; i++)
//		cout<<ST.query(i, i)<<' ';
//	cout<<endl;
//}
/*
0 0 0 0 0 0
0 2 2 2 0 0
0 2 2 3 1 1
 */