#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MM = 1e5+5;

struct LinkCut {
	struct node{
		int p = 0, ch[2] = {0, 0}, pp = 0, sz = 0;
		bool flip = 0, fix = 0;
		ll val = 0, lp = 0, fixv = 0, max = INT_MIN, min = INT_MAX;
		ll sum = 0;
	};
	vector<node> T;
	int ptr;
	
	LinkCut(int n): T(n+1){ }
	
	int newnode(int v){
		ptr++;
		T[ptr].val = v;
		T[ptr].sz = 1;
		return ptr;
	}
	
	// SPLAY TREE OPERATIONS START
	
	int dir(int x, int y){ //which ch[?] y is of x
		return T[x].ch[1] == y;
	}
	
	void set(int x, int d, int y){ //set x's ch[d] to y and y's par to x
		if(x) T[x].ch[d] = y, pull(x);
		if(y) T[y].p = x;
	}
	
	void pull(int x){
		if(!x) return;
		int l = T[x].ch[0], r = T[x].ch[1];
		push(l), push(r);
		T[x].sum = T[l].sum + T[r].sum + T[x].val;
		T[x].max = max({T[x].val, T[l].max, T[r].max});
		T[x].min = min({T[x].val, T[l].min, T[r].min});
		T[x].sz = T[l].sz + T[r].sz + 1;
	}
	
	void push(int x){
		if(!x) return;
		int &l = T[x].ch[0], &r = T[x].ch[1];
		
		if(T[x].flip){
			swap(l, r);
			T[l].flip ^= 1; T[r].flip ^= 1;
			T[x].flip = 0;
		}
		
		if(T[x].fix){
			ll v = T[x].fixv + T[x].lp;
			T[x].val = T[x].max = T[x].min = v;
			T[x].sum = (ll)v*T[x].sz;
			
			T[l].fixv = T[r].fixv = v;
			T[l].fix = T[r].fix = 1;
			T[l].lp = T[r].lp = 0;
			
			T[x].fix = 0;
			T[x].fixv = T[x].lp = 0;
		}
		else{
			auto &lp = T[x].lp;
			T[x].val += lp, T[x].max += lp, T[x].min += lp, T[x].sum += (ll)lp*T[x].sz;
			T[l].lp += lp, T[r].lp += lp;
			lp = 0;
		}
	}
	
	void rotate(int x, int d){ // 0 left, 1 right
		int y = T[x].p, z = T[y].p, w = T[x].ch[d];
		swap(T[x].pp, T[y].pp);
		set(y, !d, w);
		set(x, d, y);
		set(z, dir(z, y), x);
	}
	
	void splay(int x){
		for(push(x); T[x].p;){
			int y = T[x].p, z = T[y].p;
			push(z); push(y); push(x);
			int dx = dir(y, x), dy = dir(z, y);
			if(!z)
				rotate(x, !dx);
			else if(dx == dy)
				rotate(y, !dx), rotate(x, !dx); // zig zag
			else
				rotate(x, dy), rotate(x, dx); // zig zig
		}
	}
	
	// SPLAY TREE OPERATIONS END
	
	void makeroot(int u){
		access(u);
		int l = T[u].ch[0];
		T[l].flip ^= 1;
		swap(T[l].p, T[l].pp);
		set(u, 0, 0);
	}
	
	int access(int _u){
		int v, u;
		for(v = 0, u = _u; u; u = T[v = u].pp){ // jump both up (u is pp of v)
			splay(u); splay(v);
			//remove u's prefered child (r), change to v if it exists
			int r = T[u].ch[1];
			T[v].pp = 0;
			swap(T[r].p, T[r].pp);
			set(u, 1, v);
		}
		splay(_u);
		return v; // last node that pp jumped to (for lca)
	}
	
	void link(int u, int v){ // make v's parent u
		if(connected(u, v))
			return;
		makeroot(v);
		T[v].pp = u;
	}
	
	void cut(int u, int v){
		makeroot(u); access(u); splay(v);
		assert(T[v].pp == u);
		T[v].pp = 0;
	}
	
	bool connected(int u, int v){
		if(u == v) return 1;
		makeroot(u); access(v); splay(u);
		return T[v].p == u || T[T[v].p].p == u;
	}
	
	node query(int u, int v){
		makeroot(u); access(v);
		//now v is at top of ALL and only nodes in the splay are on path root(u) -> v
		//so it becomes subtree sum
		return T[v];
	}
	
	void update(int v, int w, bool op, ll x){
		makeroot(w), access(v);
		if(op == 0){
			T[v].lp += x;
		}
		else{
			T[v].lp = 0;
			T[v].fix = 1;
			T[v].fixv = x;
		}
	}
	
	int findroot(int u){
		access(u);
		while(T[u].ch[0])
			u = T[u].ch[0];
		splay(u);
		return u;
	}
	
	int lca(int v, int w){
		access(v);
		return access(w);
		//v already on preferred path
		//returning last time w had to jump to join preferred path (with v)
	}
	
	void wtf(int x, int y){
		//change x's par to y, unless y is in x's subtree
		if(lca(x, y) == x) return;
		access(x);
		cut(x, T[x].ch[0]);
		link(x, y);
	}
};

int n, m;
ll a[MM];

void print(ll v){
	cout<<v<<'\n';
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	LinkCut LCT(n+m+5);
	for(int i = 1; i <= n; i++){
		cin>>a[i];
		LCT.update(i, i, 1, a[i]);
	}
	for(int i = 0,x,y; i < n-1; i++){
		cin>>x>>y;
		LCT.link(x, y);
	}
	int root;
	cin>>root;
	
	ll z;
	for(int i = 0,op,x,y; i < m; i++){
		LCT.makeroot(root);
		cin>>op>>x;
		if(op == 0){
			root = x;
		}
		if(op == 1){
			cin>>y>>z;
			LCT.update(x, y, 1, z);
		}
		if(op == 2){
			cin>>y>>z;
			LCT.update(x, y, 0, z);
		}
		if(op == 3){
			cin>>y;
			print(LCT.query(x, y).min);
		}
		if(op == 4){
			cin>>y;
			print(LCT.query(x, y).max);
		}
		if(op == 5){
			cin>>y;
			print(LCT.query(x, y).sum);
		}
		if(op == 6){
			cin>>y;
			LCT.wtf(x, y);
		}
		if(op == 7){
			cin>>y;
			print(LCT.lca(x, y));
		}
	}
	
	return 0;
}

/*
 notes:
 only push during splay x, x->p, x->p->p or right before pull
 only pull in "set" function
 
 */