// overkill sol to https://atcoder.jp/contests/abc097/tasks/arc097_a
// more functions https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Heavy/SuffixAutomaton.h

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SuffixAutomaton{
	struct st{
		int len, par;
		ll cnt;
		map<char, int> ch;
	};
	vector<st> v;
	int sz, last;
	
	void init(int n){
		v.resize(n*2);
		v[0].len = 0; //0 is the root
		v[0].par = -1;
		sz = 1;
		last = 0;
	}
	
	void extend(char c){
		int cur = sz++;
		v[cur].len = v[last].len+1;
		int p = last;
		while(p != -1 && !v[p].ch.count(c)){
			v[p].ch[c] = cur;
			p = v[p].par;
		}
		if(p == -1){
			v[cur].par = 0;
		}
		else{
			int o = v[p].ch[c]; //"other"
			if(v[p].len+1 == v[o].len){
				v[cur].par = o;
			}
			else{
				int clone = sz++; //clone
				v[clone].ch = v[o].ch;
				v[clone].par = v[o].par;
				v[clone].len = v[p].len+1;
				while(p != -1 && v[p].ch[c] == o){
					//redirect all these to clone
					v[p].ch[c] = clone;
					p = v[p].par;
				}
				v[o].par = v[cur].par = clone;
			}
		}
		last = cur;
	}
	
	ll getsz(int x){
		if(v[x].cnt)
			return v[x].cnt;
		for(auto i: v[x].ch)
			v[x].cnt += getsz(i.second);
		return ++v[x].cnt;
	}
	
	string kth(int cur, int k){
		assert(k < v[cur].cnt);
		if(!k) return ""; //lexographically least
		k--;
		for(auto i: v[cur].ch){
			if(k < v[i.second].cnt)
				return i.first+kth(i.second, k);
			k -= v[i.second].cnt;
		}
		abort();
	}
} SA;

int main(){
	string s; int k;
	cin>>s>>k;
	SA.init(5000);
	for(auto c: s)
		SA.extend(c);
	SA.getsz(0);
	cout<<SA.kth(0, k)<<'\n';
}
