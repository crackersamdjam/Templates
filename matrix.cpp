#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using T = long long;
constexpr T mod = 1e9+7;

struct matrix{
	int n, m;
	vector<vector<T>> a;
	matrix(int _n = 0, int _m = 0){
		n = _n, m = _m;
		a.resize(n);
		for(int i = 0; i < n; i++)
			a[i].resize(m, 0);
	}
};

struct vect{
	int n;
	vector<T> a;
	vect(int _n = 0){
		n = _n;
		a.resize(n, 0);
	}
};

vect mul(const vect &va, const matrix &mb){
	assert(va.n == mb.n);
	vect vc(mb.m);
	for(int i = 0; i < mb.m; i++){
		for(int j = 0; j < mb.n; j++)
			vc.a[i] = (vc.a[i] + va.a[j]*mb.a[j][i])%mod;
	}
	return vc;
}

matrix mul(const matrix &ma, const matrix &mb){
	matrix c(ma.n, mb.m);
	for(int i = 0; i < ma.n; i++){
		for(int j = 0; j < mb.m; j++){
			T t = 0;
			for(int k = 0; k < ma.m; k++)
				t = (t + ma.a[i][k] * mb.a[k][j]) % mod;
			c.a[i][j] = t;
		}
	}
	return c;
}

matrix fpow(matrix m, T exp){
	if(exp == 1)
		return m;
	matrix ret = fpow(m, exp/2);
	ret = mul(ret, ret);
	if(exp&1)
		ret = mul(ret, m);
	return ret;
}

vect fpow(vect res, matrix base, int exp){
	assert(res.n == base.n);
	while(1){
		if(exp&1)
			res = mul(res, base);
		exp /= 2;
		if(!exp) break;
		base = mul(base, base);
	}
	return res;
}

int main(){
	int n; ll k;
	cin >> n >> k;
	matrix a(n, n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			cin >> a.a[i][j];
	}
	a = fpow(a, k);
	cout << a.a[0][3] << '\n';
	
	vect st(n);
	st.a[0] = 1;
	st.a[1] = 1;
	st = fpow(st, a, 10);
	cout << st.a[4] <<'\n';
}
/*
5 3
0 1 0 0 0
0 0 1 0 0
0 0 0 1 0
0 0 0 0 1
0 0 0 0 1
 */