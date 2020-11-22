#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
using namespace std;

// pi[i] = length of longest suffix (ending at i) with the same prefix as s
vector<int> kmp(string s){
	vector<int> pi(sz(s));
	pi[0] = 0;
	for(int i = 1; i < sz(s); i++){
		int j = pi[i-1];
		while(j and s[i] != s[j])
			j = pi[j-1];
		if(s[i] == s[j])
			j++;
		pi[i] = j;
	}
	return pi;
}

vector<int> kmp2(string s, const string &t){
	int sub = sz(s);
	s = s+"#"+t;
	
	vector<int> pi(sz(s)), ret(sz(t));
	pi[0] = 0;
	for(int i = 1; i < sz(s); i++){
		int j = pi[i-1];
		while(j and s[i] != s[j])
			j = pi[j-1];
		if(s[i] == s[j])
			j++;
		pi[i] = j;
		
		//if(i-sub-sub >= 0 and pi[i] == sub){
		//	// substring t[i, i+pi) matches s
		//	cout<<i-sub-sub<<' ';
		//}
	}
	for(int i = 0; i < sz(t); i++)
		ret[i] = pi[sub+1+i];
	return ret;
}
