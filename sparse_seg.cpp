// https://dmoj.ca/problem/ioi05p3
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
#define nm ((nl+nr)/2)

const int MM = 5e6;

struct node{
	int lp = 0, sum = 0, max = 0, lcp = 0, rcp = 0;
	bool up = 0;
	void pull();
	void push(int nl, int nr);
	int query(int nl, int nr, int h);
	void update(int nl, int nr, int l, int r, int v);
	void apply(int val, int k){
		sum = max = val*k;
		lp = val;
		up = 1;
	}
} nodes[MM];
int ptr = 1;

void node::pull(){
	sum = nodes[lcp].sum + nodes[rcp].sum;
	max = std::max(nodes[lcp].max, nodes[lcp].sum + nodes[rcp].max);
}

void node::push(int nl, int nr){
	if(nl != nr && !lcp){
		lcp = ++ptr;
		rcp = ++ptr;
	}
	if(up and nl != nr){
		nodes[lcp].apply(lp, nm-nl+1);
		nodes[rcp].apply(lp, nr-nm);
		up = lp = 0;
	}
}

int node::query(int nl, int nr, int h){
	if(nl == nr)
		return nl-(max > h);
	push(nl, nr);
	if(nodes[lcp].max <= h)
		return nodes[rcp].query(nm+1, nr, h-nodes[lcp].sum);
	return nodes[lcp].query(nl, nm, h);
}

void node::update(int nl, int nr, int l, int r, int v){
	if(r < nl or nr < l)
		return;
	if(l <= nl and nr <= r){
		apply(v, nr-nl+1);
		return;
	}
	push(nl, nr);
	nodes[lcp].update(nl, nm, l, r, v);
	nodes[rcp].update(nm+1, nr, l, r, v);
	pull();
}

int main(){
	int n, op, l, r, v, k;
	scan(n);
	while((op = gc) != 'E'){
		if(op == 'I'){
			scan(l, r, v);
			nodes[1].update(0, n, l, r, v);
		}
		else{
			scan(k);
			print(nodes[1].query(0, n, k));
		}
	}
}