// https://dmoj.ca/problem/lrsubtree

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
using T = long long;
using pii = pair<int, int>;
const int MM = 5e5+5, LOG = 17, mod = 1e9+7, inf = 0x3f3f3f3f;
const T DEF = 0;

int N, Q, a[MM];
vector<int> g[MM], at_dep[MM];
int tin[MM], tout[MM], timer, dep[MM], mx_dep;

struct node{
	node *l, *r;
	T sum;
	node(T val = DEF){
		l = r = nullptr;
		sum = val;
	}
	node(node *l, node *r): l(l), r(r){
		if(!l) sum = r->sum;
		else if(!r) sum = l->sum;
		else sum = l->sum + r->sum;
	}
} *rt[MM];

node *build(int nl, int nr){
	if(nl == nr) return new node(0);
	return new node(build(nl, nm), build(nm+1, nr));
}

node *upd(node *cur, int nl, int nr, int idx, ll val){
	if(nl > idx || nr < idx) return cur;
	if(nl == nr) return new node(val);
	return new node(upd(cur->l, nl, nm, idx, val), upd(cur->r, nm+1, nr, idx, val));
}

T query(node *cur, int nl, int nr, int l, int r){
	if(nl > r || nr < l) return DEF;
	else if(nl >= l && nr <= r) return cur->sum;
	return query(cur->l, nl, nm, l, r) + query(cur->r, nm+1, nr, l, r);
}

void dfs(int u, int p = -1){
	tin[u] = ++timer;
	at_dep[dep[u]].push_back(u);
	mx_dep = max(mx_dep, dep[u]);
	for (int v : g[u]) {
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
	tout[u] = timer;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	
	cin >> N >> Q;
	assert(1 <= N && N <= 5e5);
	assert(1 <= Q && Q <= 5e5);
	for (int i = 1; i <= N; i++) {
		cin >> a[i];
		assert(0 <= a[i] && a[i] <= 1e9);
	}
	for (int i = 1, u, v; i < N; i++) {
		cin >> u >> v;
		assert(1 <= u && u <= N);
		assert(1 <= v && v <= N);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	rt[0] = build(1, N);
	for (int i = 0; i <= mx_dep; i++) {
		if (i != 0) rt[i] = rt[i - 1];
		for (int u : at_dep[i]) {
			rt[i] = upd(rt[i], 1, N, tin[u], a[u]);
		}
	}
	int cnt = 0;
	ll ret = 0;
	for (int i = 0; i < Q; i++) {
		ll w, l, r;
		cin >> w >> l >> r;
		w ^= ret, l ^= ret, r ^= ret;
		if (w < 1 || w > N) {
			cerr << "bruh" << w << " " << l << " " << r << endl;
			cerr << i << endl;
		}
		assert(1 <= w && w <= N);
		assert(0 <= l && l <= N - 1);
		assert(0 <= r && r <= N - 1);
		assert(l <= r);
		if (dep[w] + l > mx_dep) {
			ret = 0;
			cout << 0 << '\n';
			continue;
		}
		r = min(dep[w] + (int) r, mx_dep);
		l = dep[w] + l - 1;
		ll sum1 = query(rt[r], 1, N, tin[w], tout[w]);
		ll sum2 = 0;
		if (l >= dep[w]) sum2 = query(rt[l], 1, N, tin[w], tout[w]);
		ret = sum1 - sum2;
		cout << ret << '\n';
		if (r != dep[w] && sum1 - sum2>0) cnt++;
	}
	cerr << cnt << endl;
	
	return 0;
}
