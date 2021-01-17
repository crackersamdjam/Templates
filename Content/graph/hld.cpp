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
using T = long long;
using L = long long;
const int MM = 5e4+5;

struct node{
	T val;
	L lp;
	int sz;
	inline void apply(L v){
		val += v*sz; //range sum
		lp += v;
	}
};

struct segtree{
#define lc (rt<<1)
#define rc (rt<<1|1)
#define nm ((nl+nr)>>1)
	node tree[MM*4];
	const T DEF = 0;
	const L LDEF = 0;
	inline T merge(T va, T vb){ return va + vb;}
	inline void pull(int rt){ tree[rt].val = merge(tree[lc].val, tree[rc].val);}
	
	// node with lazy val means yet to push to children (but updated itself)
	inline void push(int rt, int nl, int nr){
		L &val = tree[rt].lp;
		if(nl != nr){
			tree[lc].apply(val);
			tree[rc].apply(val);
		}
		val = LDEF;
	}
	
	void build(int l = 0, int r = MM-1, int rt = 1){
		int nl = l, nr = r;
		
		tree[rt].val = DEF;
		tree[rt].lp = LDEF;
		tree[rt].sz = r-l+1;
		
		if(l == r)
			return;
		build(l, nm, lc);
		build(nm+1, r, rc);
		pull(rt);
	}
	
	void update(int l, int r, L val, int nl = 0, int nr = MM-1, int rt = 1){
		if(r < nl || l > nr)
			return;
		if(l <= nl && r >= nr){
			tree[rt].apply(val);
			return;
		}
		push(rt, nl, nr);
		update(l, r, val, nl, nm, lc);
		update(l, r, val, nm+1, nr, rc);
		pull(rt);
	}
	
	T query(int l, int r, int nl = 0, int nr = MM-1, int rt = 1){
		if(r < nl || l > nr)
			return DEF;
		if(l <= nl && r >= nr)
			return tree[rt].val;
		push(rt, nl, nr);
		return merge(query(l, r, nl, nm, lc), query(l, r, nm+1, nr, rc));
	}
#undef lc
#undef rc
#undef nm
} ST;

int n, q;
vector<int> adj[MM];
int par[MM], dep[MM], heavy[MM], head[MM], in[MM], out[MM], ptr;

int dfs(int cur, int pre){
	int size = 1, maxsz = 0;
	for(int u : adj[cur]){
		if(u == pre)
			continue;
		par[u] = cur, dep[u] = dep[cur]+1;
		int szu = dfs(u, cur);
		size += szu;
		if(szu > maxsz)
			maxsz = szu, heavy[cur] = u;
	}
	return size;
}

void hld(int cur, int hd){
	head[cur] = hd;
	in[cur] = ++ptr;
	
	if(heavy[cur])
		hld(heavy[cur], hd);
	for(int u: adj[cur]){
		if(u != par[cur] && u != heavy[cur])
			hld(u, u);
	}
	out[cur] = ptr;
}

int getlca(int a, int b){
	while(head[a] != head[b]){
		if(dep[head[a]] < dep[head[b]])
			b = par[head[b]];
		else
			a = par[head[a]];
	}
	return dep[a] < dep[b] ? a : b;
}

T query(int a, int b){
	T res = 0;
	for(; head[a] != head[b]; b = par[head[b]]){
		if(dep[head[a]] > dep[head[b]])
			swap(a, b);
		res += ST.query(in[head[b]], in[b]);
	}
	if(a != b){
		if(dep[a] > dep[b])
			swap(a, b);
		res += ST.query(in[a]+1, in[b]);
	}
	return res;
}

void update(int a, int b, L v){
	for(; head[a] != head[b]; b = par[head[b]]){
		if(dep[head[a]] > dep[head[b]])
			swap(a, b);
		int l = in[head[b]], r = in[b];
		ST.update(l, r, v);
	}
	if(a != b){
		if(dep[a] > dep[b])
			swap(a, b);
		ST.update(in[a]+1, in[b], v);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i = 0,a,b; i < n-1; i++){
		cin>>a>>b;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}
	
	dfs(1, 0);
	hld(1, 1);
	ST.build();
	
	for(int i = 0,a,b; i < q; i++){
		char c;
		cin>>c>>a>>b;
		if(c == 'P')
			update(a, b, 1);
		else if(c == 'L')
			cout<<getlca(a, b)<<'\n';
		else
			cout<<query(a, b)<<'\n';
	}
}
/*
current code:
P adds 1 to each edge on path
L gets lca
Q queries sum of edges on path

5 7
1 2
2 3
2 4
1 5
L 3 4
L 1 5
P 1 3
Q 1 2
P 5 4
Q 1 2
Q 5 4

2
1
1
2
4
*/