#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
const ll mod = 1e9+9;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int k, n; cin>>k>>n;
	
	function<int(int va, int vb)> val;
	if(k == 1){
		val = [](int va, int vb){ return va^vb; };
	}
	else if(k == 2){
		val = [](int va, int vb){ return va|vb; };
	}
	else if(k == 3){
		val = [](int va, int vb){ return va&vb; };
	}
	else abort();
	
	vector<ll> a(n), b(n);
	for(int i = 0; i < n; i++)
		cin>>a[i];
	for(int i = 0; i < n; i++)
		cin>>b[i];
	vector<ll> c(2*n);
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			c[val(i, j)] += a[i]*b[j];
			c[val(i, j)] %= mod;
		}
	}
	for(int i = 0; i < 2*n; i++)
		cout<<c[i]<<' ';
	cout<<'\n';
}