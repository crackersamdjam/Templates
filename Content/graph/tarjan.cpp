#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
const int MM = 1e5+1;

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
