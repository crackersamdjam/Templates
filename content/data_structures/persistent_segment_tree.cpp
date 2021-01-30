// https://dmoj.ca/problem/lrsubtree
// this solution is a bit slower than potop's

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using ll = long long;
const int MM = 5e5+5, SZ = MM*20;

template<class T> struct pseg{
#define nm ((nl+nr)>>1)
	int ptr = 1, root[MM], lc[SZ], rc[SZ];
	T val[SZ];
	vector<pair<int, T>> add[MM];
	
	void build(){
		for(int i = 1; i < MM-2; i++){
			root[i+1] = root[i];
			for(auto [j, v]: add[i])
				update(j, v, root[i+1], 0, MM-2);
		}
	}
	
	void update(int x, T v, int &rt, int nl, int nr){
		val[ptr] = val[rt]+v;
		lc[ptr] = lc[rt], rc[ptr] = rc[rt];
		rt = ptr++;
		
		if(nl == nr) return;
		x <= nm ? update(x, v, lc[rt], nl, nm) : update(x, v, rc[rt], nm+1, nr);
	}
	
	T query(int l1, int r1, int l2, int r2){
		if(l2 > r2 or l1 > r1) return 0;
		return query(l2, r2, root[r1+1], 0, MM-2) - query(l2, r2, root[l1], 0, MM-2);
	}
	
	T query(int l, int r, int rt, int nl, int nr){
		if(r < nl or nr < l)
			return 0;
		if(l <= nl and nr <= r)
			return val[rt];
		return query(l, r, lc[rt], nl, nm) + query(l, r, rc[rt], nm+1, nr);
	}
#undef nm
}; pseg<ll> ST;

int n, q, dep[MM], in[MM], out[MM], ti;
ll dp[MM];
vector<int> adj[MM];

void dfs(int cur, int pre){
	in[cur] = ++ti;
	dep[cur] = dep[pre]+1;
	for(int u: adj[cur])
		if(u != pre)
			dfs(u, cur);
	out[cur] = ti;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>q;
	for(int i = 1; i <= n; i++)
		cin>>dp[i];
	for(int i = 0,a,b; i < n-1; i++){
		cin>>a>>b;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; i++){
		ST.add[dep[i]].emplace_back(in[i], dp[i]);
	}
	ST.build();
	
	ll last = 0;
	while(q--){
		ll u, l, r;
		cin>>u>>l>>r;
		u ^= last, l ^= last, r ^= last;
		l += dep[u];
		r += dep[u];
		ll ans = ST.query(l, r, in[u], out[u]);
		last = ans;
		cout<<ans<<'\n';
	}
}