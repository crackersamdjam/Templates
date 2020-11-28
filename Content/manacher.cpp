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

// https://cp-algorithms.com/string/manacher.html
pair<vector<int>, vector<int>> manacher(string s, bool front = 1, bool back = 1){
	if(front) s = "@"+s;
	if(back) s += "#";
	int n = (int)size(s);
	vector<int> p1(n), p2(n); //radii of palindromes (1 odd, 2 even length)
	
	for(int i = 1, mx = 0, p = 0; i < n-1; i++){
		p1[i] = (i >= mx) ? 1 : min(mx-i, p1[p*2-i]);
		while(s[i-p1[i]] == s[i+p1[i]])
			p1[i]++;
		if(i+p1[i] > mx)
			mx = i+p1[i], p = i;
	}
	for(int i = 1, mx = 0, p = 0; i < n-1; i++){
		p2[i] = (i >= mx) ? 0 : min(mx-i, p2[p*2-i+2]);
		while(s[i-p2[i]-1] == s[i+p2[i]])
			p2[i]++;
		if(i+p2[i] > mx)
			mx = i+p2[i], p = i-1;
	}
	if(front) p1.erase(p1.begin()), p2.erase(p2.begin());
	if(back) p1.pop_back(), p2.pop_back();
	return {p1, p2};
}

// https://dmoj.ca/problem/vmss7wc15c2p2
// int main(){
// 	int n; string s;
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);
// 	cin>>n>>s;
// 	auto [v1, v2] = manacher(" "+s);
// 	auto a = max_element(all(v1)), b = max_element(all(v2));
// 	if(*a*2-1 > *b*2){
// 		int l = a-v1.begin()-*a;
// 		cout<<s.substr(l, *a*2-1)<<'\n';
// 		cout<<*a*2-1<<'\n';
// 	}
// 	else{
// 		int l = b-v2.begin()-*b-1;
// 		cout<<s.substr(l, *b*2)<<'\n';
// 		cout<<*b*2<<'\n';
// 	}
// }

// https://dmoj.ca/problem/dmopc15c7p6
// using ll = long long;
// const int MM = 1e5+5;

// ll dp[MM], psa[MM], dif[MM], ans;

// int main(){
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);
// 	string s;
// 	cin>> s;
// 	int n = size(s)+1;
// 	s = " ."+s;
// 	auto [r, r2] = manacher(s);

// 	for(int i = 2; i <= n; i++){
// 		// for(int j = 0; j < r[i]; j++){
// 		// 	dp[i+j] += 1;
// 		// 	ans += dp[i-j-1];
// 		// }
// 		// for(int j = 0; j < r2[i]; j++){
// 		// 	dp[i+j] += 1;
// 		// 	ans += dp[i-j-2];
// 		// }
// 		dif[i]++;
// 		dif[i+r[i]]--;
// 		ans += psa[i-1] - psa[i-r[i]-1];

// 		dif[i]++;
// 		dif[i+r2[i]]--;
// 		ans += psa[i-2] - psa[i-r2[i]-2];

// 		dif[i] += dif[i-1];
// 		dp[i] = dp[i-1] + dif[i];
// 		psa[i] = psa[i-1] + dp[i];
// 	}

// 	cout<<ans<<'\n';
// }
