#include <bits/stdc++.h>

using namespace std;

struct LinkCut {
    struct Node {
        int p = 0, ch[2] = {0, 0}, pp = 0;
        bool flip = 0;
        int val = 0, dp = 0;
    };
    vector<Node> node;
    
    LinkCut(int n) : node(n + 1) {}
    
    // SPLAY TREE OPERATIONS START
    
    int dir(int x, int y){ //which ch[?] y is of x
        return node[x].ch[1] == y;
    }
    
    void set(int x, int d, int y){ //set x's ch[d] to y and y's par to x
        if (x) node[x].ch[d] = y, pull(x);
        if (y) node[y].p = x;
    }
    
    void pull(int x){ //aka push up
        if(!x) return;
        int &l = node[x].ch[0], &r = node[x].ch[1];
        node[x].dp = max({node[x].val, node[l].dp, node[r].dp});
    }
    
    void push(int x){ //push down
        if(!x || !node[x].flip)
            return;
        int &l = node[x].ch[0], &r = node[x].ch[1];
        swap(l, r); node[l].flip ^= 1; node[r].flip ^= 1;
        node[x].flip = 0;
    }
    
    void rotate(int x, int d){ // 0 left, 1 right
        int y = node[x].p, z = node[y].p, w = node[x].ch[d];
        swap(node[x].pp, node[y].pp);
        set(y, !d, w);
        set(x, d, y);
        set(z, dir(z, y), x);
    }
    
    void splay(int x){
        for(push(x); node[x].p;){
            int y = node[x].p, z = node[y].p;
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
    
    void MakeRoot(int u) {
        Access(u);
        int l = node[u].ch[0];
        node[l].flip ^= 1;
        swap(node[l].p, node[l].pp);
        set(u, 0, 0);
    }
    
    void Access(int _u) {
        for (int v = 0, u = _u; u; u = node[v = u].pp) {
            splay(u); splay(v);
            int r = node[u].ch[1];
            node[v].pp = 0;
            swap(node[r].p, node[r].pp);
            set(u, 1, v);
        }
        splay(_u);
    }
    
    void Link(int u, int v) {
        assert(!Connected(u, v));
        MakeRoot(v);
        node[v].pp = u;
    }
    
    void Cut(int u, int v) {
        MakeRoot(u); Access(u); splay(v);
        assert(node[v].pp == u);
        node[v].pp = 0;
    }
    
    bool Connected(int u, int v) {
        if (u == v) return true;
        MakeRoot(u); Access(v); splay(u);
        return node[v].p == u || node[node[v].p].p == u;
    }
    
    int GetPath(int u, int v) {
        MakeRoot(u); Access(v); return v;
    }
};

void Test() {
    int N = 100, Q = 100, V = 1000;
    while (true) {
        int n = rand() % N + 1;
        int q = rand() % Q + 1;
        int p1 = rand() % 100, p2 = rand() % 100, p3 = rand() % 100, p4 = rand() % 100, p5 = rand() % 100;
        
        vector<pair<int, int>> edges;
        LinkCut lc(n);
        
        auto conn = [&](int a, int b) {
            vector<int> dp(n + 1, -1);
            dp[a] = lc.node[a].val;
            for (int ch = 1; ch >= 0; ch--) {
                for (auto p : edges) {
                    for (int it = 0; it < 2; ++it) {
                        if (dp[p.first] != -1 && dp[p.second] == -1) {
                            dp[p.second] = max(dp[p.first], lc.node[p.second].val);
                            ch = 1;
                        }
                        swap(p.first, p.second);
                    }
                }
            }
            return dp[b];
        };
        
        
        auto sim_op = [&]() {
            while (true) {
                int t = rand() % (p1 + p2 + p3 + p4 + p5);
                
                if (t < p1) {
                    int a = rand() % n + 1, b = rand() % n + 1;
                    if (conn(a, b) == -1) {
                        edges.emplace_back(a, b);
                        lc.Link(a, b);
                        return;
                    }
                    continue;
                }
                
                t -= p1;
                
                if (t < p2) {
                    if (edges.empty()) continue;
                    int pos = rand() % edges.size();
                    swap(edges[pos], edges.back());
                    // cerr << "CUT: " << edges.back().first << " " << edges.back().second << endl;
                    lc.Cut(edges.back().first, edges.back().second);
                    edges.pop_back();
                    return;
                }
                
                t -= p2;
                
                if (t < p3) {
                    int node = rand() % n + 1;
                    lc.Access(node);
                    lc.node[node].val = rand() % V + 1;
                    lc.pull(node);
                    // cerr << "UPDATE: " << node << endl;
                    return;
                }
                
                t -= p3;
                
                if (t < p4) {
                    int a = rand() % n + 1, b = rand() % n + 1;
                    int expected = conn(a, b);
                    if (expected != -1) {
                        // cerr << "QUERY: " << a << " " << b << endl;
                        int ch = lc.GetPath(a, b);
                        int actual = lc.node[ch].dp;
                        assert(expected == actual);
                        return;
                    }
                    continue;
                }
                
                t -= p4;
                
                if (t < p5) {
                    int a = rand() % n + 1, b = rand() % n + 1;
                    // cerr << "CONNECTED: " << a << " " << b << endl;
                    int expected = (conn(a, b) != -1);
                    // cerr << "EXP: " << expected << endl;
                    int actual = lc.Connected(a, b);
                    assert(expected == actual);
                    return;
                }
                
                assert(false);
            }
        };
        
        for (int i = 0; i < q; ++i) {
            sim_op();
        }
        
        cerr << "OK N = " << n << " Q = " << q << endl;
    }
}

int main() {
    Test();
    return 0;
}