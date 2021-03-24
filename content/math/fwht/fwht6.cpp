// https://ccoj.ca/problem/fwht6
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
using T = ll;
using matrix = vector<vector<T>>;

const ll mod = 1e9+9;

ll gcd(ll gcd_a, ll gcd_b){return gcd_b == 0 ? gcd_a : gcd(gcd_b, gcd_a % gcd_b);}
ll fpow(ll fpow_b, ll fpow_exp, ll fpow_mod){if(fpow_exp == 0) return 1;ll t = fpow(fpow_b,fpow_exp/2,fpow_mod);if(fpow_exp&1) return t*t%fpow_mod*fpow_b%fpow_mod;return t*t%fpow_mod;}
ll fpow(ll fpow_b, ll fpow_exp){if(fpow_exp == 0) return 1;ll t = fpow(fpow_b,fpow_exp/2,mod);if(fpow_exp&1) return t*t%mod*fpow_b%mod;return t*t%mod;}
ll divmod(ll divmod_i, ll divmod_j, ll divmod_mod){divmod_i%=divmod_mod,divmod_j%=divmod_mod;return divmod_i*fpow(divmod_j,divmod_mod-2,divmod_mod)%divmod_mod;}
ll divmod(ll divmod_i, ll divmod_j){divmod_i%=mod,divmod_j%=mod;return divmod_i*fpow(divmod_j,mod-2,mod)%mod;}

const T r = 115381398, r2 = r*r%mod;
const T ir0 = (r2+r)%mod;
const T ir = -divmod(1, r), ir2 = divmod(r+1, r);

const vector<vector<T>> tmp = {{1, 1, 1}, {1, r, r2}, {1, r2, r}};
const vector<vector<T>> tmpinv = {{r2+r, -1, -1}, {-1, divmod(-1, r), divmod(r+1, r)}, {-1, divmod(r+1, r), divmod(-1, r)}};
const T det = divmod(1, (r2+r-2)%mod);

void go(vector<T> &v){
	int n = size(v);
	for(int len = 1; len < n; len *= 3){
		for(int pos = 0; pos < n; pos += len*3){
			for(int i = 0; i < len; i++){
				// replace values v[pos+i] v[pos+i+len] with their product with T_2
				T a = v[pos+i];
				T b = v[pos+i+len];
				T c = v[pos+i+len+len];
				v[pos+i] = (a + b + c) % mod;
				v[pos+i+len] = (a + r*b + r2*c) % mod;
				v[pos+i+len+len] = (a + r2*b + r*c) % mod;
			}
		}
	}
}
void invgo(vector<T> &v){
	int n = size(v);
	for(int len = 1; len < n; len *= 3){
		for(int pos = 0; pos < n; pos += len*3){
			for(int i = 0; i < len; i++){
				T a = v[pos+i];
				T b = v[pos+i+len];
				T c = v[pos+i+len+len];
				v[pos+i] = (ir0*a - b - c) % mod * det % mod;
				v[pos+i+len] = (-a + ir*b + ir2*c) % mod * det % mod;
				v[pos+i+len+len] = (-a + ir2*b + ir*c) % mod * det % mod;
			}
		}
	}
}

void mul(vector<T> &va, vector<T> &vb){
	int n = 1;
	while(n < size(va))
		n *= 3;
	n *= 3;
	va.resize(n), vb.resize(n);
	go(va); go(vb);
	for(int i = 0; i < n; i++){
		va[i] *= vb[i];
		va[i] %= mod;
	}
	invgo(va);
}

// matrix matmul(matrix ma, matrix mb){
// 	matrix c(3);
// 	for(int i = 0; i < 3; i++){
// 		c[i].resize(3);
// 		for(int j = 0; j < 3; j++){
// 			T t = 0;
// 			for(int k = 0; k < 3; k++)
// 				t = (t + ma[i][k] * mb[k][j]);
// 			c[i][j] = t/det;
// 		}
// 	}
// 	return c;
// }

int main(){
//	freopen("../in", "r", stdin);
	// cout<<fpow(3, 333333336, mod)<<endl;
	// cout<<fpow(5, mod-1, mod)<<endl;
	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin>>k>>n;
	vector<T> a(n), b(n);
	for(int i = 0; i < n; i++){
		cin>>a[i];
	}
	for(int i = 0; i < n; i++){
		cin>>b[i];
	}
	
	mul(a, b);
	a.resize(3*n);
	for(int i = 0; i < 3*n; i++){
		if(a[i] < 0) a[i] += mod;
		cout<<a[i]<<' ';
		// cout<<round(a[i].real())<<' ';
	}
	cout<<'\n';
}