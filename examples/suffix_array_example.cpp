#include "../content/string/suffix_array.h"
// https://dmoj.ca/src/3133739
// https://dmoj.ca/problem/fbwheels
// https://www.facebook.com/codingcompetitions/hacker-cup/2014/final-round/problems/C
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using ll = long long;
using ld = double;
constexpr int MM = 1e5+5;

int tc, tt, n, m, k, w, x, y, z;
string s;
ll dp[MM];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin>>tc;
	cout<<fixed<<setprecision(3);
	while(tc--){
		tt++;
		cin>>k>>m>>w>>x>>y>>z;
		cin>>s;
		n = size(s);
		for(int i = 0; i < n; i++)
			dp[i] = LLONG_MAX/3;
		dp[0] = -w;

		while(k--){
			int a, b;
			cin>>a>>b;
			for(int i = b; i < n; i++)
				dp[i] = min(dp[i], dp[i-b]+a+w);
		}

		auto v = suffix_array_construction(s, 128);
		auto lcp = lcp_construction(s, v);
		vector<vector<int>> add(n);
		for(int i = 0; i < size(lcp); i++)
			add[lcp[i]].emplace_back(i);

		vector<ld> ans;
		//if i in st, then i and i+1 have lcp <= len
		set<int> st;
		st.insert(-1);
		st.insert((int)size(lcp));

		multiset<ll> ins;
		ins.insert((ll)n*(n-1));
		// options to take

		for(int len = 0; len < n; len++){

			if(len){
				int t = m;
				for(auto it = ins.rbegin(); it != ins.rend(); it++){
					if(!t--)
						break;

					ll tot = (ll)(n-len+1)*(n-len);
					ld p = (ld)*it/tot;
					ll sq = n - abs(x-len);
					ll v = y*sq*sq+z;
					ld all = p*v-dp[len];
					ans.emplace_back(all);
				}
			}

			for(auto i: add[len]){
				auto it = st.lower_bound(i);
				auto pre = it;
				pre--;
				ll d = *it-*pre;
				ins.erase(ins.lower_bound(d*(d-1)));

				d = i-*pre;
				ins.insert(d*(d-1));

				d = *it-i;
				ins.insert(d*(d-1));

				st.insert(i);
			}
		}
		sort(all(ans), greater<ld>());
		ll none = -*min_element(dp+1, dp+n);
		while(size(ans) < m)
			ans.emplace_back(none);
		
		// cout<<"Case #"<<tt<<": ";
		for(int i = 0; i < m; i++)
			cout<<max((ld)none, ans[i])<<' ';
		cout<<'\n';

	}
}
/*
Two moves are distinct if they involve purchasing different sequences of letters – the deal(s) used are ignored
*/