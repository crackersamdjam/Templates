#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
const int MM = 5005;
const ll mod = 1e9+9;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int k, n; cin>>k>>n;
	
	function<int(int va, int vb)> val;
	if(k == 6){
		val = [](int va, int vb){
			int vc = 0;
			for(int i = 3; i < MM; i *= 3){
				int rem = ((va%i)+(vb%i))%i;
				vc += rem;
				va -= va%i;
				vb -= vb%i;
			}
			return vc;
		};
	}
	else abort();
	
	vector<ll> a(n), b(n);
	for(int i = 0; i < n; i++)
		cin>>a[i];
	for(int i = 0; i < n; i++)
		cin>>b[i];
	vector<ll> c(3*n);
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			c[val(i, j)] += a[i]*b[j];
			c[val(i, j)] %= mod;
		}
	}
	for(int i = 0; i < 3*n; i++)
		cout<<c[i]<<' ';
	cout<<'\n';
}