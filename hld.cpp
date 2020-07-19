#include <bits/stdc++.h>
using namespace std;
typedef long long T;
const int MM = 5e4+5;

struct node{
	T val, lp;
	int sz;
	inline void apply(T v){
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
	inline T merge(T va, T vb){ return va + vb;}
	inline void pull(int rt){ tree[rt].val = merge(tree[lc].val, tree[rc].val);}
	
	// node with lazy val means yet to push to children (but updated itself)
	inline void push(int rt, int nl, int nr){
		T &val = tree[rt].lp;
		if(nl != nr){
			tree[lc].apply(val);
			tree[rc].apply(val);
		}
		val = DEF;
	}
	
	void build(int l = 0, int r = MM-1, int rt = 1){
		int nl = l, nr = r;
		
		tree[rt].val = DEF;
		tree[rt].lp = 0;
		tree[rt].sz = r-l+1;
		
		if(l == r)
			return;
		build(l, nm, lc);
		build(nm+1, r, rc);
		pull(rt);
	}
	
	void update(int l, int r, T val, int nl = 0, int nr = MM-1, int rt = 1){
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

int n;
vector<int> adj[MM];
int par[MM], dep[MM], heavy[MM], head[MM], pos[MM], ptr;

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

void decompose(int cur, int id){
	head[cur] = id, pos[cur] = ++ptr;
	if(~heavy[cur])
		decompose(heavy[cur], id);
	for(int u: adj[cur]){
		if (u != par[cur] && u != heavy[cur])
			decompose(u, u);
	}
}

void init(){
	memset(heavy, -1, sizeof heavy);
	ptr = 0;
	adj[0].push_back(1);
	adj[1].push_back(0);
	dfs(0, -1);
	decompose(1, 1);
	ST.build();
}

T query(int a, int b){
	T res = 0;
	for(; head[a] != head[b]; b = par[head[b]]){
		if(dep[head[a]] > dep[head[b]])
			swap(a, b);
		res += ST.query(pos[head[b]], pos[b]);
	}
	if(a != b){
		if(dep[a] > dep[b])
			swap(a, b);
		res += ST.query(pos[a]+1, pos[b]);
	}
	return res;
}

void update(int a, int b, T v){
	for(; head[a] != head[b]; b = par[head[b]]){
		if(dep[head[a]] > dep[head[b]])
			swap(a, b);
		int l = pos[head[b]], r = pos[b];
		ST.update(l, r, v);
	}
	if(a != b){
		if(dep[a] > dep[b])
			swap(a, b);
		ST.update(pos[a]+1, pos[b], v);
	}
}