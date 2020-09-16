// https://dmoj.ca/problem/ds4
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MM = 6e5+5;

//mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
//mt19937_64 g((uint64_t) new char);
mt19937_64 g(0);
int randint(int l, int r){return uniform_int_distribution<int>(l, r)(g);}
ll randll(ll l, ll r){return uniform_int_distribution<ll>(l, r)(g);}

#define lc T[x].l
#define rc T[x].r

struct node{
	ll pr = g();
	int l = 0, r = 0, key = 0, sz = 0;
	// here val == key
} T[MM];

int ptr;

int next(int val){
	T[++ptr].key = val;
	return ptr;
}

void pull(int x){
	if(!x) return;
	T[x].sz = 1+T[lc].sz+T[rc].sz;
}

// >= key
void split(int x, int key, int &l, int &r){
	if(!x) l = r = 0;
	else if(T[x].key >= key){
		split(lc, key, l, lc);
		r = x;
	}
	else{
		split(rc, key, rc, r);
		l = x;
	}
	pull(x);
}

void merge(int &x, int l, int r){
	if(!l or !r)
		x = l?l:r;
	else if(T[l].pr > T[r].pr){
		merge(T[l].r, T[l].r, r);
		x = l;
	}
	else{
		merge(T[r].l, l, T[r].l);
		x = r;
	}
	pull(x);
}

int kth(int x, int k){
	if(k < T[lc].sz)
		return kth(lc, k);
	k -= T[lc].sz;
	if(!k)
		return T[x].key;
	k--;
	return kth(rc, k);
}

int ord(int x, int k, int i=1){
	if(!x) return 1e9;
	if(T[x].key < k)
		return ord(rc, k, i+T[lc].sz+1);
	int cur = T[x].key == k ? T[lc].sz+i : 1e9;
	return min(cur, ord(lc, k, i));
}

void out(int x){
	if(!x) return;
	out(lc);
	cout<<T[x].key<<' ';
	out(rc);
}

int n, m, last, rt, ls, rs;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	while(n--){
		int v;
		cin>>v;
		split(rt, v, rt, rs);
		merge(rt, rt, next(v));
		merge(rt, rt, rs);
	}
	char op; int v;
	while(m--){
		cin>>op>>v;
		v ^= last;
		if(op == 'I'){
			split(rt, v, rt, rs);
			merge(rt, rt, next(v));
			merge(rt, rt, rs);
		}
		if(op == 'R'){
			split(rt, v+1, rt, rs);
			split(rt, v, rt, ls);
			merge(ls, T[ls].l, T[ls].r);
			merge(rt, rt, ls);
			merge(rt, rt, rs);
		}
		if(op == 'S'){
			cout<<(last=kth(rt, v-1))<<'\n';
		}
		if(op == 'L'){
			int r = ord(rt, v);
			if(r >= 1e9)
				r = -1;
			cout<<(last=r)<<'\n';;
		}
	}
	out(rt);
}