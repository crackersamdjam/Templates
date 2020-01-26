#include <bits/stdc++.h>
using namespace std;
using T = int;
const int MM = 1e5+2;

struct node{
    T val, lp;
    bool up;
    void apply(T v){
        val += v;
        lp += v;
        up = 1;
    }
};

struct segtree{
#define lc (rt<<1)
#define rc (rt<<1|1)
#define nm ((nl+nr)>>1)
    node tree[MM*4];
    T DEF = 0;
    //default value
    
    T merge(T va, T vb){
        return va + vb;
    }
    
    void push_up(int rt){
        tree[rt].val = merge(tree[lc].val, tree[rc].val);
    }
    
    // node with lazy val means yet to push to children (but updated itself)
    void push_down(int rt, int nl, int nr){
        T &val = tree[rt].lp;
        if(tree[rt].up && nl != nr){
            tree[lc].apply(val);
            tree[rc].apply(val);
        }
        val = DEF;
        tree[rt].up = 0;
    }
    
    void build(int l = 0, int r = MM-1, int rt = 1){
        int nl = l, nr = r;
        if(l == r){
            tree[rt].val = DEF;
            tree[rt].lp = 0;
            tree[rt].up = 0;
            return;
        }
        build(l, nm, lc);
        build(nm+1, r, rc);
        push_up(rt);
    }
    
    void update(int l, int r, T val, int nl = 0, int nr = MM-1, int rt = 1){
        if(r < nl || l > nr)
            return;
        if(l <= nl && r >= nr){
            tree[rt].apply(val);
            return;
        }
        push_down(rt, nl, nr);
        update(l, r, val, nl, nm, lc);
        update(l, r, val, nm+1, nr, rc);
        push_up(rt);
    }
    
    T query(int l, int r, int nl = 0, int nr = MM-1, int rt = 1){
        if(r < nl || l > nr)
            return DEF;
        if(l <= nl && r >= nr)
            return tree[rt].val;
        push_down(rt, nl, nr);
        return merge(query(l, r, nl, nm, lc), query(l, r, nm+1, nr, rc));
    }
#undef lc
#undef rc
#undef nm
} t;

int n, m;
vector<int> adj[MM];
int par[MM], depth[MM], heavy[MM], head[MM], pos[MM], ptr;

int dfs(int cur, int pre){
    int size = 1, maxsz = 0;
    for(int u : adj[cur]){
        if(u == pre)
            continue;
        par[u] = cur, depth[u] = depth[cur]+1;
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
    dfs(1, -1);
    decompose(1, 1);
    t.build();
}

int query(int a, int b){
    int res = 0;
    for(; head[a] != head[b]; b = par[head[b]]){
        if(depth[head[a]] > depth[head[b]])
            swap(a, b);
        res += t.query(pos[head[b]], pos[b]);
    }
    if(a != b){
        if(depth[a] > depth[b])
            swap(a, b);
        res += t.query(pos[a]+1, pos[b]);
    }
    return res;
}

void update(int a, int b){
    for(; head[a] != head[b]; b = par[head[b]]){
        if(depth[head[a]] > depth[head[b]])
            swap(a, b);
        int l = pos[head[b]], r = pos[b];
        t.update(l, r, 1);
    }
    if(a != b){
        if(depth[a] > depth[b])
            swap(a, b);
        t.update(pos[a]+1, pos[b], 1);
    }
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i = 0,a,b; i < n-1; i++){
        cin >> a >> b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    
    init();
    
    for(int i = 0,a,b; i < m; i++){
        char c;
        cin >> c >> a >> b;
        if(c == 'P')
            update(a, b);
        else
            cout << query(a, b) << '\n';
    }
    
    return 0;
}
