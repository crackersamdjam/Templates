#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;

template<typename T> struct pt{
	T x, y;
	pt() {}
	pt(T _x, T _y): x(_x), y(_y) {}
	pt& operator += (const pt &o){
		x += o.x, y += o.y;
		return *this;
	}
	pt& operator -= (const pt &o){
		x -= o.x, y -= o.y;
		return *this;
	}
	pt operator *= (T o){
		x *= o, y *= o;
		return *this;
	}
	pt operator /= (T o){
		x /= o, y /= o;
		return *this;
	}
	pt operator + (const pt &o) const{
		return pt(*this) += o;
	}
	pt operator - (const pt &o) const{
		return pt(*this) -= o;
	}
	pt operator * (const pt &o) const{
		return pt(*this) *= o;
	}
	pt operator / (const pt &o) const{
		return pt(*this) /= o;
	}
};

int main(){

	pt a = {1, 2};
//	pt b = a*5;

}

namespace old{
	const int MM = 55;
	using ld = double;
	
	int n;
	double x[MM], y[MM], ans = 1e16;
	
	
	double dis(double x1, double y1, double x2, double y2){
		return sqrtl((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	}
	void check(double cx, double cy){
		double mx = 0;
		for(int i=0; i<n; i++)
			mx = max(mx, dis(x[i], y[i], cx, cy));
		ans = min(ans, mx);
		//cout << cx << ' ' << cy << ' ' << mx << '\n';
	}
	//centroid of three points
	void cent(int a, int b, int c){
		ld a1 = x[b]-x[a], b1 = y[b]-y[a], c1 = (a1*a1 + b1*b1)/2;
		ld a2 = x[c]-x[a], b2 = y[c]-y[a], c2 = (a2*a2 + b2*b2)/2;
		ld d = a1*b2 - a2*b1;
		//watch out for infinate coordinates
		if(d != 0)
			check(x[a] + (c1*b2 - c2*b1)/d, y[a] + (a1*c2 - a2*c1)/d);
	}
	
	//two centers of circle where two points are on it if radius is 2.5
	void solve(int a, int b){
		double mx = (x[a] + x[b])/2, my = (y[a] + y[b])/2, m = 0.0;
		if(x[a] != x[b]) m = -(x[a] - x[b])/(y[a]-y[b]);
		double d = sqrt(6.25 - dis(x[a], y[a], mx, my));
		double dx = d / sqrt(1+m*m), dy = d*m/sqrt(1+m*m);
		check(mx-dx, my-dy); check(mx+dx, my+dy);
	}
}