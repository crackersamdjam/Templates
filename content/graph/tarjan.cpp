#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;

namespace oldTemplates{
	constexpr int MM = 1e5+5;
	int dfn[MM], low[MM], t, path[MM], ptr;
	bool ins[MM];
	vector<int> adj[MM];
	
	//find SCCs/BCCs
	struct sccbcc{
		void dfs(int cur, int pre){
			
			ins[cur] = 1;
			path[++ptr] = cur;
			dfn[cur] = low[cur] = ++t;
			
			for(int u: adj[cur]){
				if(u == pre) //only for bidirectional? need fix
					
					continue;
				if(!dfn[u]){
					dfs(u, cur);
					low[cur] = min(low[cur], low[u]);
				}
				else if(ins[u])
					low[cur] = min(low[cur], dfn[u]);
				// 'else if(ins[u])' for SCC
				// 'else' for BCC
			}
			
			if(dfn[cur] == low[cur]){
				int u = -1;
				while(u != cur){
					u = path[ptr--];
					ins[u] = 0;
				}
			}
		}
		
	};
	
	bool vis[MM];
	set<int> ans;
	
	// find articulation points
	struct art{
		void dfs(int cur, int pre){
			for(int &u: adj[cur]){
				if(u != pre){
					if(!vis[u]){
						vis[u] = 1;
						dfn[u] = low[u] = ++t;
						dfs(u, cur);
						
						low[cur] = min(low[cur], low[u]);
						
						if(pre == -1 && low[u] > dfn[cur])
							ans.insert(cur);
						if(pre != -1 && low[u] >= dfn[cur])
							ans.insert(cur);
					}
					else
						low[cur] = min(low[cur], dfn[u]);
				}
			}
		}
		//alternative
		/*
		void dfs(int v, int p = -1) {
			visited[v] = true;
			tin[v] = low[v] = timer++;
			int children=0;
			for (int to : adj[v]) {
				if (to == p) continue;
				if (visited[to]) {
					low[v] = min(low[v], tin[to]);
				} else {
					dfs(to, v);
					low[v] = min(low[v], low[to]);
					if (low[to] >= tin[v] && p!=-1)
						IS_CUTPOINT(v);
					++children;
				}
			}
			if(p == -1 && children > 1)
				IS_CUTPOINT(v);
		}
		 */
	};
	
	set<pair<int, int>> bridges;
	
	//find bridges
	struct br{
		void dfs(int cur, int pre){
			for(int &u: adj[cur]){
				if(u != pre){
					if(!vis[u]){
						vis[u] = 1;
						dfn[u] = low[u] = ++t;
						dfs(u, cur);
						
						low[cur] = min(low[cur], low[u]);
		
						if(low[u] > dfn[cur])
							bridges.insert({u, cur});
							
					}
					else
						low[cur] = min(low[cur], dfn[u]);
				}
			}
		}
	};
};

namespace SCC{
	constexpr int MM = 5e5+5;
	vector<int> adj[MM];
	int dfn[MM], low[MM], t, id[MM];
	bool ins[MM];
	stack<int> stk;
	vector<vector<int>> scc;
	
	void dfs(int cur){
		dfn[cur] = low[cur] = ++t;
		stk.push(cur);
		ins[cur] = 1;
		
		for(auto u: adj[cur]){
			if(!dfn[u]){
				dfs(u);
				low[cur] = min(low[cur], low[u]);
			}
			else if(ins[u])
				low[cur] = min(low[cur], dfn[u]);
		}
		
		if(dfn[cur] == low[cur]){
			int u = -1;
			scc.emplace_back();
			while(u != cur){
				u = stk.top(); stk.pop();
				ins[u] = 0;
				id[u] = cur;
				scc.back().emplace_back(u);
			}
		}
	}
} using namespace SCC;

// https://old.yosupo.jp/problem/scc
namespace SCCSAMP{
	int main(){
		ios_base::sync_with_stdio(0);
		cin.tie(0);
		int n, m;
		cin>>n>>m;
		for(int i = 0,a,b; i < m; i++){
			cin>>a>>b;
			if(a != b)
				adj[a].emplace_back(b);
		}
		for(int i = 0; i < n; i++){
			if(!dfn[i])
				dfs(i);
		}
		cout<<size(scc)<<'\n';
		reverse(all(scc));
		for(auto &&v: scc){
			cout<<size(v);
			for(auto i: v)
				cout<<' '<<i;
			cout<<'\n';
		}
		// for(int i = 0; i < n; i++)
		// cerr<<id[i]<<' ';
		return 0;
	}
};

int main(){
	SCCSAMP::main();
}