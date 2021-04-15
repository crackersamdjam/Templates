#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
using namespace std;

int n = 5;

#include "../content/data_structures/segment_tree_simple.h"
Segtree ST;

int main(){
	
	ST.build(0, n);
	ST.update(1, 2, 3);
	ST.update(2, 5, 1);
	ll res = ST.query(2, 3);
	cout<<res<<'\n';
}
// this needs a better test