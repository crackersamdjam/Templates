#pragma once
#include "point.h"
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

// monotone chain algorithm
vector<pt> convex_hull(vector<pt> pts){
	sort(all(pts));
	vector<pt> hull;
	for(int h = 0; h < 2; h++){
		int last = size(hull);
		for(int i = 0; i < size(pts); i++){
			while(size(hull) >= last+2 and ccw(*(hull.end()-2), pts[i], hull.back()) >= 0)
				hull.pop_back();
			hull.push_back(pts[i]);
		}
		hull.pop_back();
		reverse(all(pts));
	}
	if(size(hull) == 2 and hull[0] == hull[1])
		hull.pop_back();
	if(!size(hull) and size(pts))
		hull.push_back(pts[0]);
	return hull;
}