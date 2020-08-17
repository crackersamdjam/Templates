// https://dmoj.ca/problem/dmopc16c3p6

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define gc getchar()
#define pc(x) putchar(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

#ifndef ONLINE_JUDGE
template<typename T>
void pr(T a){std::cerr<<a<<std::endl;}
template<typename T,typename... Args>
void pr(T a, Args... args) {std::cerr<<a<<' ',pr(args...);}
#else
template<typename... Args>
void pr(Args... args){}
#endif

#define nm ((nl+nr)>>1)

using namespace std;
using T = int;
const int MM = 1e5+5, NN = 5e5+5;

int n, q, ptr;
T a[MM];

struct node{
	node *l, *r;
	T sum, pre, suf;
	node(T val){
		l = r = nullptr;
		pre = suf = sum = val;
	}
	node(node *_l, node *_r): l(_l), r(_r){   // merge function
		sum = l->sum + r->sum;
		pre = max(l->pre, l->sum + r->pre);
		suf = max(r->suf, l->suf + r->sum);
	}
	node *copy(){
		node *ret = new node(*this);
		ret->l = ret->r = 0;
		return ret;
	}
	~node(){
		if(l) delete l;
		if(r) delete r;
	}
} *rt[NN], *NDEF;

void init(){ // initalize NOT DEFINED (does not exist) node
	NDEF = new node(0);
	NDEF->pre = NDEF->suf = INT_MIN/2;
	NDEF->sum = 0;
}

node *build(int nl, int nr){
	if(nl == nr) return new node(a[nl]);
	return new node(build(nl, nm), build(nm+1, nr));
}

node *update(node *cur, int nl, int nr, int idx, T val){
	if(nl > idx || nr < idx) return cur;
	if(nl == nr) return new node(val);
	return new node(update(cur->l, nl, nm, idx, val), update(cur->r, nm+1, nr, idx, val));
}

node *query(node *cur, int nl, int nr, int l, int r){
	if(nl > r || nr < l) return NDEF->copy();
	else if(nl >= l && nr <= r) return cur->copy();
	return new node(query(cur->l, nl, nm, l, r), query(cur->r, nm+1, nr, l, r));
}

// debug segtree
void out(node *cur, int nl, int nr){
	pr(nl, nr, cur->sum, cur->pre, cur->suf);
	if(nl == nr)
		return;
	out(cur->l, nl, nm); out(cur->r, nm+1, nr);
}

int main(){
	init();
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i = 1; i <= n; i++)
		cin>>a[i];
	rt[ptr] = build(1, n);
	
	cin>>q;
	for(int i = 1,x,y; i <= q; i++){
		char op;
		cin>>op;
		if(op == 'U'){
			cin>>x>>y;
			rt[ptr+1] = update(rt[ptr], 1, n, x, y);
			ptr++;
		}
		else if(op == 'G'){
			cin>>x;
			rt[ptr+1] = rt[x];
			ptr++;
		}
		else if(op == 'P'){
			cin>>x>>y;
			auto ret = query(rt[ptr], 1, n, x, y);
			cout<<ret->pre<<'\n';
			delete ret;
		}
		else if(op == 'S'){
			cin>>x>>y;
			auto ret = query(rt[ptr], 1, n, x, y);
			cout<<ret->suf<<'\n';
			delete ret;
		}
		else abort();
	}
}