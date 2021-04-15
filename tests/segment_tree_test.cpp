#include "../content/data_structures/segment_tree.h"

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;

Segtree<int, int> ST;

int main(){
	
	ST.init(0, 5);
	ST.update(1, 2, 3);
	ST.update(2, 5, 1);
	cout<<ST.query(2, 3)<<'\n';
}
// this needs a better test