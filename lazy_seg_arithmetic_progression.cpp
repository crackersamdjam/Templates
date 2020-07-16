#include <bits/stdc++.h>
using namespace std;

const int MM = 1e6+2, SZ = MM*4;

struct ari_seg{
#define lc (rt<<1)
#define rc (rt<<1|1)
#define nm ((nl+nr)>>1)
	int K[SZ], D[SZ], LK[SZ], LD[SZ], S[SZ];
	
	void push_up(int rt){
		S[rt] = S[lc] + S[rc];
	}
	
	void push_down(int nl, int nr, int rt){
		if(LK[rt] == 0 && LD[rt] == 0)
			return;
		int sz = (nr-nl+1)/2;
		K[lc] += LK[rt];
		K[rc] += LK[rt]+LD[rt]*sz;
		D[lc] += LD[rt];
		D[rc] += LD[rt];
		S[lc] += LK[rt]*sz + LD[rt]*sz*(sz-1)/2;
		S[rc] += (LK[rt]+LD[rt]*sz)*sz + LD[rt]*sz*(sz-1)/2;
		LK[lc] += LK[rt];
		LK[rc] += LK[rt]+LD[rt]*sz;
		LD[lc] += LD[rt];
		LD[rc] += LD[rt];
		LK[rt] = LD[rt] = 0;
	}
	
	int query(int l, int r, int nl = 1, int nr = MM-1, int rt = 1){
		if(nl > r || nr < l)
			return 0;
		if(nl >= l && nr <= r)
			return S[rt];
		push_down(nl, nr, rt);
		return query(l, r, nl, nm, lc) + query(l, r, nm + 1, nr, rc);
	}
	
	//add from l to r, first term = k, dif = d
	
	void update(int l, int r, int k, int d, int nl = 1, int nr = MM-1, int rt = 1){
		if(nl >= l && nr <= r){
			K[rt] += k, D[rt] += d;
			LK[rt] += k, LD[rt] += d;
			int sz = (nr-nl+1);
			S[rt] += k * sz + d * sz * (sz-1)/2;
			return;
		}
		push_down(nl, nr, rt);
		if(l <= nm) update(l, min(nm, r), k, d, nl, nm, lc);
		if(r > nm) update(max(nm+1, l), r, k + d*max(nm-l+1, 0), d, nm+1, nr, rc);
		push_up(rt);
	}
#undef lc
#undef rc
#undef nm
} T;

int n, q;

int main(){
	scanf("%d%d", &n, &q);
	for(int i = 0,t,l,r,d; i < q; i++){
		scanf("%d", &t);
		if(t == 1){
			scanf("%d%d%d", &l, &r, &d);
			T.update(l,r,d,d);
		}
		else{
			scanf("%d%d", &l, &r);
			printf("%d\n", T.query(l,r));
		}
	}
}