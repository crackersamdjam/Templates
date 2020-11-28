#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define gc getchar()
#define pc(x) putchar(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=char(n%10+48);n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;

vector<int> m1, m2;

pair<vector<int>, vector<int>> manacher(string s, bool front = 1, bool back = 1){
	if(front) s = "@"+s;
	if(back) s += "#";
	int n = (int)size(s);
	vector<int> p1(n), p2(n);
	
	m1.resize(n);
	m2.resize(n);
	
	for(int i = 1, mx = 0, p = 0; i < n-1; i++){
		p1[i] = (i >= mx) ? 1 : min(mx-i, p1[p*2-i]);
		while(s[i-p1[i]] == s[i+p1[i]])
			p1[i]++;
		if(i+p1[i] > mx)
			mx = i+p1[i], p = i;
		
		m1[i-p1[i]+1] = max(m1[i-p1[i]+1], i);
	}
	for(int i = 1, mx = 0, p = 0; i < n-1; i++){
		p2[i] = (i >= mx) ? 0 : min(mx-i, p2[p*2-i+2]);
		while(s[i-p2[i]-1] == s[i+p2[i]])
			p2[i]++;
		if(i+p2[i] > mx)
			mx = i+p2[i], p = i-1;
		
		m2[i-p2[i]] = max(m2[i-p2[i]], i);
	}
	if(front) p1.erase(p1.begin()), p2.erase(p2.begin()), m1.erase(m1.begin()), m2.erase(m2.begin());
	if(back) p1.pop_back(), p2.pop_back(), m1.pop_back(), m2.pop_back();
	return {p1, p2};
}

// https://cp-algorithms.com/string/z-function.html
// z[i] = longest common prefix between s and s[i, end]
// z[0] is defined to be 0
vector<int> zed(string s){
	int n = (int)size(s);
	vector<int> z(n);
	for(int i = 1, l = 0, r = 0; i < n; i++){
		if(i <= r)
			z[i] = min(r-i+1, z[i-l]);
		while(i+z[i] < n and s[z[i]] == s[i+z[i]])
			z[i]++;
		if(i+z[i]-1 > r)
			l = i, r = i+z[i]-1;
	}
	return z;
}

// https://dmoj.ca/problem/dmopc17c2p4
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string s;
	cin>>s;
	int n = (int)size(s);
	auto [p1, p2] = manacher(s);
	auto z = zed(s);
	int ans = 0;
	
	for(int i = 0; i < n; i++){
		m1[i]--;
		m2[i]--;
	}
	for(int i = 1; i < n; i++){
		m1[i] = max(m1[i], m1[i-1]);
		m2[i] = max(m2[i], m2[i-1]);
	}
	
	for(int i = 1; i < n; i++){
		int la = (m1[i]-i)*2+1, lb = (m2[i]-i)*2;
		if(la <= z[i])
			ans = max(ans, la);
		if(lb <= z[i])
			ans = max(ans, lb);
	}
	cout<<ans<<'\n';
}