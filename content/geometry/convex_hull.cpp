#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using T = double;
using pt = complex<T>;
#define x real()
#define y imag()

T dot(pt a, pt b){ return a.x*b.x + a.y*b.y; }
T norm(pt a){ return dot(a, a); } //norm is distance squared
T cross(pt a, pt b){ return a.x*b.y - a.y*b.x; }
pt intersectpt(pt a1, pt b1, pt a2, pt b2){
	//lines a1-b1 and a2-b2
	pt d1 = b1-a1, d2 = b2-a2;
	return a1 + cross(a2-a1, d2)/cross(d1, d2)*d1;
}

int main(){
	pt a = {1, 2};
	a *= a;
	cout<<a.x<<' '<<a.y<<'\n';
}

//int main(){
//	int tc = 5;
//	while(tc--){
//		int n, m;
//		cin>>n>>m;
//		vector<pt> v(n);
//		for(auto &[a, b]: v){
//			cin>>a>>b;
//		}
//		auto w = convexhull(v);
//		n = size(w);
//		int ans = 0;
//		for(int i = 0; i < n; i++){
//			int j = (i+1)%n;
//			ans += m*ceil(dist(w[i], w[j]));
//			// pr(w[i], w[j], dist(w[i], w[j]));
//		}
//		cout<<"$"<<ans<<".00\n";
//	}
//}