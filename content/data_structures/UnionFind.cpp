#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;

struct UnionFindBipartite{
	vector<int> par, sz;
	vector<char> parity, odd;
	void init(int MM){
		par.resize(MM);
		iota(all(par), 0);
		sz.resize(MM, 1);
		parity.resize(MM);
		odd.resize(MM);
	}
	pair<int, int> find(int x){
		int v = 0;
		while(x != par[x]){
			v ^= parity[x];
			x = par[x];
		}
		return {x, v};
	}
	bool merge(int x, int y){
		auto [a, va] = find(x);
		auto [b, vb] = find(y);
		if(a == b){
			if(!odd[a] and va == vb){
				odd[a] = 1;
				return 1;
			}
		}
		else{
			if(sz[a] > sz[b])
				swap(a, b), swap(va, vb);
			par[a] = b;
			sz[b] += sz[a];
			odd[b] |= odd[a];
			if(va == vb)
				parity[a] ^= 1;
			return 1;
		}
		return 0;
	}
};

// https://dmoj.ca/problem/oly19practice44
namespace game_of_palindrome{
	const int MM = 5005, NN = 5e5+5;
	vector<int> adj[MM];
	int n, m, qu;
	string s;
	array<int, 2> e[NN];
	bool vis[MM][MM];
	queue<pair<int, int>> q;
	UnionFindBipartite dsu[2];
	
	int main(){
		ios_base::sync_with_stdio(0);
		cin.tie(0);
		
		cin>>n>>m>>qu>>s;
		s = " "+s;
		dsu[0].init(MM);
		dsu[1].init(MM);
		
		for(int i = 0,a,b; i < m; i++){
			cin>>a>>b;
			e[i] = {a, b};
			bool f = s[a] == s[b];
			if(dsu[f].merge(a, b)){
				adj[a].emplace_back(b);
				adj[b].emplace_back(a);
			}
		}
		for(int i = 1; i <= n; i++){
			vis[i][i] = 1;
			q.emplace(i, i);
			for(int j: adj[i]){
				if(s[i] == s[j]){
					vis[i][j] = 1;
					q.emplace(i, j);
				}
			}
		}
		while(size(q)){
			auto [a, b] = q.front(); q.pop();
			if(!vis[b][a]){
				vis[b][a] = 1;
				q.emplace(b, a);
			}
			for(int c: adj[a]){
				for(int d: adj[b]){
					if(s[c] == s[d] and !vis[c][d]){
						vis[c][d] = 1;
						q.emplace(c, d);
					}
				}
			}
		}
		while(qu--){
			int a, b; cin>>a>>b;
			cout<<(vis[a][b] ? "YES\n" : "NO\n");
		}
		return 0;
	}
}

int main(){
	game_of_palindrome::main();
}