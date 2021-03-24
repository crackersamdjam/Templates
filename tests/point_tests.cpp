#include "../content/geometry/point.h"
#include <bits/stdc++.h>
using namespace std;

namespace test{
	void main(){
		pt a1 = {1, 1}, b1 = {3, 3};
		pt a2 = {2, 2}, b2 = {4, 4};
		pt c = intersect(a1, b1, a2, b2);
		cout<<c.x<<' '<<c.y<<endl;
		cout<<isnan(c.x)<<endl;
		cout<<isnan(-c.x)<<endl;
	}
}

namespace ccc06s3{
	// bruce code https://dmoj.ca/src/2941660
	int a,b,c,d,n;
	int main(){
		cin>>a>>b>>c>>d;
		pt start={a,b}, finish={c,d};
		cin>>n;
		int ans = 0;
		for(int i = 0; i < n; i++){
			int corners; cin >> corners;
			vector<pt> pt(corners);
			for(int j=0; j<corners; j++){
				cin>>pt[j];
			}
			for(int j = 0; j < corners; j++){
				if(has_intersect(start, finish, pt[j], pt[(j+1)%corners])){
					ans++; break;
				}
			}
		}
		cout<<ans<<'\n';
	}
}

int main(){
//	ccc06s3::main();
}