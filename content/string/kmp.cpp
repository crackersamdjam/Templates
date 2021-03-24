#include <bits/stdc++.h>
using namespace std;

// pi[i] = length of longest proper prefix equal to suffix of s ending at i ( s.substr(0, i+1) )
vector<int> kmp(string s){
	vector<int> pi(size(s));
	pi[0] = 0;
	for(int i = 1, j = 0; i < size(s); i++){
		while(j and s[i] != s[j])
			j = pi[j-1];
		if(s[i] == s[j])
			j++;
		pi[i] = j;
	}
	return pi;
}

vector<int> kmp2(string s, const string &t){
	int sub = size(s);
	s = s+"#"+t;
	
	vector<int> pi(size(s)), ret(size(t));
	pi[0] = 0;
	for(int i = 1; i < size(s); i++){
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
	for(int i = 0; i < size(t); i++)
		ret[i] = pi[sub+1+i];
	return ret;
}
