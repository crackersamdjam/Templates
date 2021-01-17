// https://dmoj.ca/problem/tle17c7p4
// cmp(a, b) compares two strings lexicographically
// this works in O(F) time where F is the sum of all the edit distances of strings s[i-1] and s[i]

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
using ll = long long;
const int MM = 2e5+5;
const ll base = 131, mod = 1e9+7;

int n, m, q;
ll pw[MM];
char s[MM];

struct node{
	node *l, *r;
	ll hash;
	char c;
	int sz;
	node(char _c){
		l = r = nullptr;
		hash = c = _c;
		sz = 1;
	}
	node(node *_l, node *_r): l(_l), r(_r){
		hash = (l ? l->hash : 0) * pw[(r ? r->sz : 0)] + (r ? r->hash : 0);
		sz = (l ? l->sz : 0) + (r ? r->sz : 0);
	}
} *rt[MM];

node *build(int nl, int nr){
	if(nl == nr) return new node(s[nl]);
	return new node(build(nl, nm), build(nm+1, nr));
}

node *update(node *cur, int nl, int nr, int idx, char val){
	if(nl > idx || nr < idx) return cur;
	if(nl == nr) return new node(val);
	return new node(update(cur->l, nl, nm, idx, val), update(cur->r, nm+1, nr, idx, val));
}

char query(node *cur, int nl, int nr, int l, int r){
	if(nl > r || nr < l) return 0;
	else if(nl >= l && nr <= r) return cur->c;
	return query(cur->l, nl, nm, l, r) + query(cur->r, nm+1, nr, l, r);
}

// void out(node *cur, int nl, int nr){
// 	if(cur->sz == 1) pr(nl, nr, cur->sz, cur->hash, cur->c);
// 	else pr(nl, nr, cur->sz, cur->hash);
// 	if(nl == nr)
// 		return;
// 	out(cur->l, nl, nm); out(cur->r, nm+1, nr);
// }

bool cmp(node *a, node *b){
	if(a->sz == 1)
		return a->c < b->c;
	if(a->l->hash == b->l->hash)
		return cmp(a->r, b->r);
	return cmp(a->l, b->l);
}

int main(){
	scanf("%s", s+1);
	m = strlen(s+1);
	pw[0] = 1;
	for(int i = 1; i <= m; i++)
		pw[i] = pw[i-1]*base;
	
	scan(n);
	rt[1] = build(1, m);
	for(int i = 2; i <= n; i++){
		int j; char c;
		scan(j); c = gc;
		rt[i] = rt[i-1];
		rt[i] = update(rt[i], 1, m, j, c);
	}
	
	// for(int i = 1; i <= n; i++){
	// 	pr("out", i);
	// 	out(rt[i], 1, m);
	// }
	
	sort(rt+1, rt+1+n, cmp);
	scan(q);
	while(q--){
		int i, j;
		scan(i, j);
		auto ret = query(rt[i], 1, m, j, j);
		pc(ret);
		pc(10);
	}
}