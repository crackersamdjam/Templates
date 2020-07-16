#include <bits/stdc++.h>
using namespace std;
constexpr int MM = 2e5+5;

mt19937 g1(time(0));
int randint(int a, int b){return uniform_int_distribution<int>(a, b)(g1);}

#define l T[x].lc
#define r T[x].rc
struct node{
	int pr = randint(0, INT_MAX), val = 0, sz = 0, max = 0, lv = 0, rv = 0, flip = 0;
	int lc = 0, rc = 0;
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

void split(int x, int k, int &ls, int &rs, int add){
	push(x);
	int cur = add + T[l].sz; //current key
	if(!x) ls = rs = 0;
	else if(k <= cur){
		split(l, k, ls, l, add);
		rs = x;
	}
	else{
		split(r, k, r, rs, add+1+T[l].sz);
		ls = x;
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
	}
	else{
		merge(T[rs].lc, ls, T[rs].lc);
		x = rs;
	}
	pull(x);
}

int n, q, rt, mid, rs;
string s;

void out(int x){
	if(!x) return;
	push(x);
	out(l);
	cout << T[x].val << ' ';
	out(r);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>q>>s;
	for(int i = 1; i <= n; i++){
		T[i].val = (s[i-1]=='1');
		merge(rt, rt, i);
	}
	
	while(q--){
		int op, a, b;
		cin>>op>>a>>b;
		a++;
		b = a+b-1;
		if(op == 1){
			split(rt, b, rt, rs, 0);
			split(rt, a-1, rt, mid, 0);
//			cout<<"ls "; out(rt); cout<<'\n'; cout<<"mid "; out(mid); cout<<'\n'; cout<<"rs "; out(rs); cout<<'\n'; cout<<'\n';
			T[mid].flip ^= 1;
			merge(mid, mid, rs);
			merge(rt, rt, mid);
		}
		else{
			split(rt, b, rt, rs, 0);
			split(rt, a-1, rt, mid, 0);
			cout << T[mid].max << '\n';
			
//			cout<<"ls "; out(rt); cout<<'\n'; cout<<"mid "; out(mid); cout<<'\n'; cout<<"rs "; out(rs); cout<<'\n'; cout<<'\n';
			
			merge(mid, mid, rs);
			merge(rt, rt, mid);
		}
//		out(rt); cout<<'\n';
	}
	
	return 0;
}
