// https://ccoj.ca/problem/fwht1
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
const ll mod = 1e9+9;

ll gcd(ll gcd_a, ll gcd_b){return gcd_b == 0 ? gcd_a : gcd(gcd_b, gcd_a % gcd_b);}
ll fpow(ll fpow_b, ll fpow_exp, ll fpow_mod){if(fpow_exp == 0) return 1;ll t = fpow(fpow_b,fpow_exp/2,fpow_mod);if(fpow_exp&1) return t*t%fpow_mod*fpow_b%fpow_mod;return t*t%fpow_mod;}
ll divmod(ll divmod_i, ll divmod_j, ll divmod_mod){divmod_i%=divmod_mod,divmod_j%=divmod_mod;return divmod_i*fpow(divmod_j,divmod_mod-2,divmod_mod)%divmod_mod;}

struct fwht{
	using T = ll;
	T w, x, y, z;
	fwht(T w, T x, T y, T z): w(w), x(x), y(y), z(z) {}
//	const T w = 1, x = 1, y = 1, z = -1;
//	const T w = 1, x = 1, y = 1, z = 0;
//	const T w = 0, x = 1, y = 1, z = 1;
	const T det = divmod(1, w*z-x*y, mod);
	// calculate transform matrix http://serbanology.com/show_article.php?art=A%20Bitwise%20Convolution%20Tutorial
	// fwht::mul in input vectors A, B and output vector C, v[i] = [# of ways / probability/ any value of type T] to get a mask of i
	// fwht can be used for bitwise operators
	// xor: w,x,y,z = 1,1,1,-1
	// or: w,x,y,z = 1,1,1,0
	// and: w,x,y,z = 0,1,1,1
	
	void go(vector<T> &v){
		int n = size(v);
		for(int len = 1; len < n; len *= 2){
			for(int pos = 0; pos < n; pos += len*2){
				for(int i = 0; i < len; i++){
					// replace values v[pos+i] v[pos+i+len] with their product with T_2
					T a = v[pos+i];
					T b = v[pos+i+len];
					v[pos+i] = (w*a+x*b)%mod;
					v[pos+i+len] = (y*a+z*b)%mod;
				}
			}
		}
	}
	void invgo(vector<T> &v){
		int n = size(v);
		for(int len = 1; len < n; len *= 2){
			for(int pos = 0; pos < n; pos += len*2){
				for(int i = 0; i < len; i++){
					// replace values v[pos+i] v[pos+i+len] with their product with the inverse of T_2
					T a = v[pos+i];
					T b = v[pos+i+len];
					v[pos+i] = (z*a-y*b)%mod * det % mod;
					v[pos+i+len] = (w*b-x*a)%mod * det % mod;
				}
			}
		}
	}
	void mul(vector<T> &va, vector<T> &vb){
		int n = size(va)+size(vb)-1;
		while(n&(n-1)) n++;
		va.resize(n), vb.resize(n);
		go(va); go(vb);
		for(int i = 0; i < n; i++)
			va[i] *= vb[i];
		invgo(va);
	}
};

fwht *T;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int k, n; cin>>k>>n;
	if(k == 1)
		T = new fwht(1, 1, 1, -1);
	else if(k == 2)
		T = new fwht(1, 1, 1, 0);
	else if(k == 3)
		T = new fwht(0, 1, 1, 1);
	else abort();
	
	vector<ll> a(n), b(n);
	for(int i = 0; i < n; i++)
		cin>>a[i];
	for(int i = 0; i < n; i++)
		cin>>b[i];
	T->mul(a, b);
	for(int i = 0; i < 2*n; i++){
		if(a[i] < 0) a[i] += mod;
		cout<<a[i]<<' ';
	}
}