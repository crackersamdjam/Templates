#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MM = 2002;

struct sparse_table{
	int n; ll sp[12][MM];
	ll query(int a, int b){
		int k = 31-__builtin_clz(b-a+1);
		print(max(sp[k][a], sp[k][b-(1<<k)+1]));
	}
	void build(int _n){
		n = _n;
		for(int k = 1; k <= 31-__builtin_clz(n); k++)
			for(int i = 0; i+(1<<k)-1 <= n; i++)
				sp[k][i] = max(sp[k-1][i], sp[k-1][i+(1<<(k-1))]);
	}
};
