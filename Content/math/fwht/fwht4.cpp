// https://ccoj.ca/problem/fwht4
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
using T = ll;
using matrix = vector<vector<int>>;
const ll mod = 1e9+9;

ll gcd(ll gcd_a, ll gcd_b){return gcd_b == 0 ? gcd_a : gcd(gcd_b, gcd_a % gcd_b);}
ll fpow(ll fpow_b, ll fpow_exp, ll fpow_mod){if(fpow_exp == 0) return 1;ll t = fpow(fpow_b,fpow_exp/2,fpow_mod);if(fpow_exp&1) return t*t%fpow_mod*fpow_b%fpow_mod;return t*t%fpow_mod;}
ll divmod(ll divmod_i, ll divmod_j, ll divmod_mod){divmod_i%=divmod_mod,divmod_j%=divmod_mod;return divmod_i*fpow(divmod_j,divmod_mod-2,divmod_mod)%divmod_mod;}

struct fwht4{
	void go(vector<T> &v){
		int n = size(v);
		for(int len = 1; len < n; len *= 4){
			for(int pos = 0; pos < n; pos += len*4){
				for(int i = 0; i < len; i++){
					// replace values v[pos+i] v[pos+i+len] with their product with T_2
					// cout<<pos+i<<' '<<pos+i+len*3<<endl;
					T a = v[pos+i];
					T b = v[pos+i+len];
					T c = v[pos+i+len+len];
					T d = v[pos+i+len+len+len];
					v[pos+i] = (c+d)%mod;
					v[pos+i+len] = c;
					v[pos+i+len+len] = (a+b+c+d)%mod;
					v[pos+i+len+len+len] = (a+c)%mod;
				}
			}
		}
	}
	
	void inv(vector<T> &v){
		int n = size(v);
		for(int len = 1; len < n; len *= 4){
			for(int pos = 0; pos < n; pos += len*4){
				for(int i = 0; i < len; i++){
					// replace values v[pos+i] v[pos+i+len] with their product with T_2
					T a = v[pos+i];
					T b = v[pos+i+len];
					T c = v[pos+i+len+len];
					T d = v[pos+i+len+len+len];
					v[pos+i] = (-b+d)%mod;
					v[pos+i+len] = (-a+b+c-d)%mod;
					v[pos+i+len+len] = b;
					v[pos+i+len+len+len] = (a-b)%mod;
				}
			}
		}
	}
	
	void mul(vector<T> &va, vector<T> &vb){
		int n = size(va)+size(vb)-1;
		while(n&(n-1)) n++;
		if(__builtin_ctz(n) % 2)
			n <<= 1;
		va.resize(n), vb.resize(n);
		go(va); go(vb);
		for(int i = 0; i < n; i++){
			va[i] *= vb[i];
			va[i] %= mod;
		}
		inv(va);
	}
};

struct fwht5{
//vector<vector<int>> tmp = {{0, 0, 1, 1}, {0, 0, 1, 0}, {1, 1, 1, 1}, {1, 0, 1, 0}};
//vector<vector<int>> tmpinv = {{0, -1, 0, 1}, {-1, 1, 1, -1}, {0, 1, 0, 0}, {1, -1, 0, 0}};
//int divval = 1;
	vector<vector<int>> tmp = {{0, 0, 1, 1, 0,  0,  1,  1},
							   {0, 0, 1, 0, 0,  0,  1,  0},
							   {1, 1, 1, 1, 1,  1,  1,  1},
							   {1, 0, 1, 0, 1,  0,  1,  0},
							   {0, 0, 1, 1, 0,  0,  -1, -1},
							   {0, 0, 1, 0, 0,  0,  -1, 0},
							   {1, 1, 1, 1, -1, -1, -1, -1},
							   {1, 0, 1, 0, -1, 0,  -1, 0}};
	vector<vector<int>> tmpinv = {{0,  -1, 0, 1,  0,  -1, 0,  1},
								  {-1, 1,  1, -1, -1, 1,  1,  -1},
								  {0,  1,  0, 0,  0,  1,  0,  0},
								  {1,  -1, 0, 0,  1,  -1, 0,  0},
								  {0,  -1, 0, 1,  0,  1,  0,  -1},
								  {-1, 1,  1, -1, 1,  -1, -1, 1},
								  {0,  1,  0, 0,  0,  -1, 0,  0},
								  {1,  -1, 0, 0,  -1, 1,  0,  0}};
	T det = divmod(1, 2, mod);
	
	void matmul(vector<T> &va, const matrix &mb){
		int n = size(mb);
		vector<T> vc(n);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				vc[i] += mb[i][j]*va[j];
				vc[i] %= mod;
			}
		}
		va = vc;
	}
	
	void go(vector<T> &v){
		int n = size(v);
		for(int len = 1; len < n; len *= 8){
			for(int pos = 0; pos < n; pos += len * 8){
				for(int i = 0; i < len; i++){
					vector<T> cc(8);
					for(int k = 0; k < 8; k++)
						cc[k] = v[pos+i+len*k];
					matmul(cc, tmp);
					for(int k = 0; k < 8; k++)
						v[pos+i+len*k] = cc[k];
				}
			}
		}
	}
	
	void inv(vector<T> &v){
		int n = size(v);
		for(int len = 1; len < n; len *= 8){
			for(int pos = 0; pos < n; pos += len * 8){
				for(int i = 0; i < len; i++){
					vector<T> cc(8);
					for(int k = 0; k < 8; k++)
						cc[k] = v[pos+i+len*k];
					matmul(cc, tmpinv);
					for(int k = 0; k < 8; k++)
						v[pos+i+len*k] = cc[k]*det%mod;
				}
			}
		}
	}
	
	void mul(vector<T> &va, vector<T> &vb){
		int n = size(va)+size(vb)-1;
		while(n&(n-1)) n++;
		while(__builtin_ctz(n) % 3)
			n <<= 1;
		va.resize(n), vb.resize(n);
		go(va); go(vb);
		for(int i = 0; i < n; i++){
			va[i] *= vb[i];
			va[i] %= mod;
		}
		inv(va);
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int k, n; cin>>k>>n;
	vector<ll> a(n), b(n);
	for(int i = 0; i < n; i++)
		cin>>a[i];
	for(int i = 0; i < n; i++)
		cin>>b[i];
	
	if(k == 4){
		fwht4 T;
		T.mul(a, b);
	}
	else if(k == 5){
		fwht5 T;
		T.mul(a, b);
	}
	else abort();
	
	for(int i = 0; i < 2*n; i++){
		if(a[i] < 0) a[i] += mod;
		cout<<a[i]<<' ';
	}
}