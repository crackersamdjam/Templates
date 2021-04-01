#pragma once
#include <bits/stdc++.h>
using namespace std;

template<class T> struct sparse_table{
	int n; vector<vector<T>> sp;
	T query(int l, int r){
		int k = __lg(r-l+1);
		return min(sp[k][l], sp[k][r-(1<<k)+1]);
	}
	void build(vector<T> v){
		n = size(v);
		sp.resize(__lg(n)+1);
		sp[0] = v;
		for(int i = 1; i <= __lg(n); i++){
			sp[i].resize(n, -1);
			for(int j = 0; j+(1<<i)-1 < n; j++){
				sp[i][j] = min(sp[i-1][j], sp[i-1][j+(1<<(i-1))]);
			}
		}
	}
};