#pragma once
#include "point.h"

T getarea(vector<pt> v){
	T a = 0;
	for(int i = 2; i < size(v); i++)
		a += ccw(v[0], v[i-1], v[i]);
	return a;
}