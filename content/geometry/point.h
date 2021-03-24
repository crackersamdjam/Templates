#pragma once
#include <bits/stdc++.h>
using namespace std;

//using T = double; constexpr T eps = 1e-7;
using T = int; constexpr T eps = 0;
using pt = complex<T>;
#define x real()
#define y imag()

bool operator<(const pt &a, const pt &b){
	return a.x < b.x or (abs(a.x-b.x) <= eps and a.y < b.y-eps);}
bool operator==(const pt &a, const pt &b){
	return abs(a.x-b.x) <= eps and abs(a.y-b.y) <= eps;}
bool operator<=(const pt &a, const pt &b){
	return a < b or a == b;}

T dot(pt a, pt b){ return a.x*b.x + a.y*b.y;}
T norm(pt a){ return dot(a, a); } // norm is distance squared
T cross(pt a, pt b){ return a.x*b.y - a.y*b.x;} // right hand rule: a-index, b-middle, cross-thumb. Result is > 0 if ccw, < 0 if cw, 0 if collinear.
T ccw(pt origin, pt a, pt b){ return cross(a-origin, b-origin);}

pt intersect(pt a1, pt a2, pt b1, pt b2){
	// lines a1-a2 and b1-b2
	pt d1 = a2-a1, d2 = b2-b1;
	return a1 + cross(b1-a1, d2)/cross(d1, d2) * d1;
}
bool has_intersect(pt a1, pt a2, pt b1, pt b2){
	if(max(a1.x, a2.x) >= min(b1.x, b2.x) && max(b1.x, b2.x) >= min(a1.x, a2.x) &&
		max(a1.y, a2.y) >= min(b1.y, b2.y) && max(b1.y, b2.y) >= min(a1.y, a2.y)
		&& ccw(a1, a2, b1) * ccw(a1, a2, b2) <= 0
		&& ccw(b1, b2, a1) * ccw(b1, b2, a2) <= 0)
		return 1;
	return 0;
}

istream &operator >> (istream &stream, pt &p){
	T X, Y; stream>>X>>Y; p = pt(X, Y); return stream;}
ostream &operator << (ostream &stream, const pt &p){
	return stream<<p.x<<' '<<p.y;}

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