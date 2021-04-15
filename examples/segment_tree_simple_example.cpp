#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
using T = ll;
using L = ll;
constexpr int MM = 5e5+5;

int n = 5;

#include "../content/data_structures/segment_tree_simple.h"
Segtree ST;

int main(){
	
	ST.build(0, n);
	ST.update(1, 2, 3);
	ST.update(2, 5, 1);
	cout<<ST.query(2, 3)<<'\n';
}
// this needs a better test