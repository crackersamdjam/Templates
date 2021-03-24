#pragma once
#include <bits/stdc++.h>
using namespace std;

template<class T> struct sparse_table{
	int n; vector<vector<T>> sp;
	T query(int l, int r){
		int k = __lg(b-a+1);
		print(max(sp[k][a], sp[k][b-(1<<k)+1]));
	}
	void build(vector<T> v){
		n = size(v);
		sp.resize(__lg(n));
		for(int k = 1; k <= __lg(n); k++){
			sp.resize(n);
			for(int i = 0; i+(1<<k)-1 <= n; i++)
				sp[k][i] = max(sp[k-1][i], sp[k-1][i+(1<<(k-1))]);
		}
	}
};
// make sure to test this later