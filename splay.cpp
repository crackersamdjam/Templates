#include <bits/stdc++.h>
using namespace std;
const int MM = 6e5+5;

struct Splay{
	struct node{
		int p = 0, ch[2] = {0, 0}, pp = 0, sz = 0;
		bool flip = 0;
		int val = 0, dp = 0;
	};
	vector<node> T;
	int ptr, root;
	
	Splay(){
		T.resize(MM);
	}
	
	int newnode(int v){
		ptr++;
		T[ptr].val = v;
		T[ptr].sz = 1;
		return ptr;
	}
	
	int dir(int x, int y){ //which ch[?] y is of x
		return T[x].ch[1] == y;
	}
	
	void set(int x, int d, int y){ //set x's ch[d] to y and y's par to x
		if(x) T[x].ch[d] = y, pull(x);
		if(y) T[y].p = x;
	}
	
	void pull(int x){ //aka push up
		if(!x) return;
		int &l = T[x].ch[0], &r = T[x].ch[1];
		T[x].dp = max({T[x].val, T[l].dp, T[r].dp});
		T[x].sz = T[l].sz + T[r].sz + 1;
	}
	
	void push(int x){ //push down
		if(!x || !T[x].flip)
			return;
		int &l = T[x].ch[0], &r = T[x].ch[1];
		swap(l, r); T[l].flip ^= 1; T[r].flip ^= 1;
		T[x].flip = 0;
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
		root = x;
	}
	
	void insert(int v){
		if(!root){
			root = newnode(v);
			return;
		}
		int x = root;
		while(1){
			//if(T[x].val == v) multiset
			  //  break;
				
			if(v <= T[x].val){
				if(T[x].ch[0])
					x = T[x].ch[0];
				else{
					set(x, 0, newnode(v));
					break;
				}
			}
			else{
				if(T[x].ch[1])
					x = T[x].ch[1];
				else{
					set(x, 1, newnode(v));
					break;
				}
			}
		}
		splay(x);
	}
	
	void inorder(int x){
		if(!x) return;
		inorder(T[x].ch[0]);
		printf("%d ", T[x].val);
		inorder(T[x].ch[1]);
	}
	
	int find(int v){
		if(!root) return 0;
		int x = root, y = 0;
		while(1){
			if(T[x].val == v){
				y = x;
			}
			if(T[x].val >= v){ // so that same # always gets leftmost one
				if(T[x].ch[0])
					x = T[x].ch[0];
				else
					break;
			}
			else{
				if(T[x].ch[1])
					x = T[x].ch[1];
				else
					break;
			}
		}
		splay(x);
		x = y;
		return (T[x].val == v ? x : 0);
	}
	
	bool erase(int v){
		int x = find(v);
		if(x < 1) return 0;
		splay(x);
		
		int y = T[x].ch[0];
		if(!y){
			root = T[x].ch[1]; //make rc root
			T[root].p = 0;
			return 1;
		}
		T[y].p = 0;
		//disconnect lc and rt
		
		while(T[y].ch[1])
			y = T[y].ch[1];
		
		splay(y);
		// y is new root
		assert(!T[y].ch[1]); //y is largest
		set(y, 1, T[x].ch[1]);
		root = y;
		return 1;
	}
	
	int orderof(int x){
		splay(x);
		return T[T[x].ch[0]].sz;
	}
	
	int kth(int k){
		int x = root;
		while(1){
			
			if(T[T[x].ch[0]].sz > k){
				x = T[x].ch[0];
				continue;
			}
			k -= T[T[x].ch[0]].sz;
			if(!k)
				break;
			k--;
			x = T[x].ch[1];
		}
		splay(x);
		return T[x].val;
	}
} ST;


int main(){
	int n, m, v, last = 0;
	char c;
	
	scanf("%d %d", &n, &m);
	
	while(n--){
		scanf("%d", &v);
		ST.insert(v);
	}
	
	while(m--){
		scanf(" %c %d", &c, &v);
		v ^= last;
		if(c == 'I'){
			ST.insert(v);
		}
		else if(c == 'R'){
			ST.erase(v);
		}
		else if(c == 'S'){
			printf("%d\n", last = ST.kth(v-1));
		}
		else{
			int id = ST.find(v);
			int r = id ? ST.orderof(id) : -2;
			printf("%d\n", last = r+1);
		}
	}
	
	ST.inorder(ST.root);
	
	return 0;
}
