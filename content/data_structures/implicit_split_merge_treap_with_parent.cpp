// test this on a problem later
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MM = 2e5+5;

//mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
//mt19937_64 g((uint64_t) new char);
mt19937_64 g(25);

#define l T[x].lc
#define r T[x].rc

struct node{
	unsigned long long pr = g();
	int val = 0, sz = 0, max = 0, lv = 0, rv = 0;
	bool flip = 0;
	int lc = 0, rc = 0, p = 0;
} T[MM];

void push(int x){
	if(!x) return;
	if(T[x].flip){
		swap(T[x].lv, T[x].rv);
		swap(l, r);
		T[l].flip ^= 1;
		T[r].flip ^= 1;
		T[x].flip = 0;
	}
}

void pull(int x){
	if(!x) return;
	push(l);
	push(r);
	T[x].sz = 1 + T[l].sz + T[r].sz;
	
	T[x].lv = T[l].lv;
	if(T[x].val and T[l].lv == T[l].sz)
		T[x].lv += 1 + T[r].lv;
	
	T[x].rv = T[r].rv;
	if(T[x].val and T[r].rv == T[r].sz)
		T[x].rv += 1 + T[l].rv;
	
	T[x].max = max({T[x].val, T[x].lv, T[x].rv, T[x].val*(T[l].rv + 1 + T[r].lv), T[l].max, T[r].max});
}

// ls gets <= k (inclusive)
void split(int x, int k, int &ls, int &rs, int add){
	T[x].p = 0;
	push(x);
	int cur = add + T[l].sz; //current key
	if(!x) ls = rs = 0;
	else if(k <= cur){
		split(l, k, ls, l, add);
		rs = x;
		T[l].p = x;
	}
	else{
		split(r, k, r, rs, add+1+T[l].sz);
		ls = x;
		T[r].p = x;
	}
	pull(x);
}

void merge(int &x, int ls, int rs){
	push(ls); push(rs);
	if(!x) x = ls ? ls : rs;
	if(!ls || !rs)
		x = ls ? ls : rs;
	else if(T[ls].pr > T[rs].pr){
		merge(T[ls].rc, T[ls].rc, rs);
		x = ls;
		T[r].p = x;
	}
	else{
		merge(T[rs].lc, ls, T[rs].lc);
		x = rs;
		T[l].p = x;
	}
	pull(x);
}

void out(int x){
	if(!x) return;
	push(x);
	out(l);
	cout<<T[x].val<<' ';
	out(r);
}

// index of node T[x] in the bbst
int ord(int x, int ch = -1){
	if(!x) return 0;
	return (l != ch)*(T[l].sz+1) + ord(T[x].p, x);
}

#undef l
#undef r

int main(){
	// add this later
}