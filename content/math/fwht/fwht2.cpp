#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
using ll = long long;
const ll mod = 1e9+7;

ll gcd(ll gcd_a, ll gcd_b){return gcd_b == 0 ? gcd_a : gcd(gcd_b, gcd_a % gcd_b);}
ll fpow(ll fpow_b, ll fpow_exp, ll fpow_mod){if(fpow_exp == 0) return 1;ll t = fpow(fpow_b,fpow_exp/2,fpow_mod);if(fpow_exp&1) return t*t%fpow_mod*fpow_b%fpow_mod;return t*t%fpow_mod;}
ll divmod(ll divmod_i, ll divmod_j, ll divmod_mod){divmod_i%=divmod_mod,divmod_j%=divmod_mod;return divmod_i*fpow(divmod_j,divmod_mod-2,divmod_mod)%divmod_mod;}

template<class T> struct matrix: vector<vector<T>>{
	int n, m;
	matrix(int N, int M): n(N), m(M){
		for(int i = 0; i < N; i++)
			this->push_back(vector<T>(M, 0));
	}
	matrix(vector<vector<T>> v): n(v.size()), m(v[0].size()){
		*this = v;
	}
};

template<class T> matrix<T> mul(matrix<T> ma, matrix<T> mb){
	matrix<T> c(ma.n, mb.m);
	for(int i = 0; i < ma.n; i++){
		for(int j = 0; j < mb.m; j++){
			T t = 0;
			for(int k = 0; k < ma.m; k++)
				t = (t + ma[i][k] * mb[k][j]) % mod;
			c[i][j] = t;
		}
	}
	return c;
}

template<class T> T getdet(matrix<T> &a){
	T ret = 1;
	for(int i = 0; i < a.n; i++){
		int mx = i;
		for(int j = i+1; j < a.n; j++)
			if(a[j][i] > a[mx][i])
				mx = j;
		if(i != mx){
			ret = -ret;
			a[i].swap(a[mx]);
		}
		for(int j = i+1; j < a.n; j++){
			T alpha = a[j][i]/a[i][i];
			for(int k = i+1; k < a.n; k++){
				a[j][k] -= alpha*a[i][k];
			}
		}
	}
	for(int i = 0; i < a.n; i++)
		ret *= a[i][i];
	return ret;
}

template<class T> void go(vector<T> &v, matrix<int> &hd){
	int n = size(v);
	for(int len = 1; len < n; len *= 2){
		for(int pos = 0; pos < n; pos += len*2){
			for(int i = 0; i < len; i++){
				// replace values v[pos+i] v[pos+i+len] with their product with T_2
				T a = v[pos+i];
				T b = v[pos+i+len];
				v[pos+i] = w*a+x*b;
				v[pos+i+len] = y*a+z*b;
			}
		}
	}
}
template<class T> void invgo(vector<T> &v, matrix<int> &hd){
	int n = size(v);
	T det = getdet(hd);
	for(int len = 1; len < n; len *= 2){
		for(int pos = 0; pos < n; pos += len*2){
			for(int i = 0; i < len; ++i) {
				// replace values v[pos+i] v[pos+i+len] with their product with the inverse of T_2
				T a = v[pos+i];
				T b = v[pos+i+len];
				v[pos+i] = (z*a-y*b)/det;
				v[pos+i+len] = (w*b-x*a)/det;
			}
		}
	}
}
template<class T> void mul(vector<T> &va, vector<T> &vb, matrix<int> &hd){
	int n = size(va)+size(vb)-1;
	while(n&(n-1)) n++;
	va.resize(n), vb.resize(n);
	go(va, hd); go(vb, hd);
	for(int i = 0; i < n; i++)
		va[i] *= vb[i];
	invgo(va, hd);
}

int main(){
	matrix<int> hd({{1, 1}, {1, 0}});
	
	vector<int> a = {1, 2}, b = {3, 4};
	mul(a, b, hd);
	for(int i: a)
		cout<<i<<' ';

//	matrix m(2, 2);
//	vector<vector<T>> v = {{1, 1}, {1, -1}};
//	vector<vector<T>> v = {{1, 1}, {1, 0}};
//	vector<vector<T>> v = {{0, 1}, {1, 1}};
//	for(int i = 0; i < 2; i++){
//		for(int j = 0; j < 2; j++){
//			m[i][j] = v[i][j];
//		}
//	}
//	print(getdet(m));
}
