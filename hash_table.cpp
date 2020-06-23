#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int M = 4500007;

void add(pii &x, pii y){
	x.first = max(x.first, y.first);
	x.second = min(x.second, y.second);
}

struct hashmap{
	ll key[M];
	pii val[M];
	int to[M], nxt[M], vis[M], sz, null=1;
	void clear(){
		sz = 0; null++;
	}
	pii update(ll x, pii v){
		int cur = x%M;
		if(vis[cur] != null)
			vis[cur] = null, to[cur] = -1;
		for(cur = to[cur]; cur != -1; cur = nxt[cur])
			if(key[cur] == x){
				add(val[cur], v);
				return val[cur];
			}
		cur = x%M; nxt[sz] = to[cur]; to[cur] = sz; val[sz] = v; key[sz] = x;
		return val[sz++];
	}
} test;

mt19937_64 g(0);
ll randl(ll a,ll b){return uniform_int_distribution<ll>(a, b)(g);}

std::chrono::time_point<std::chrono::system_clock> START, END;
chrono::duration<double> tot;

const int MM = 4e6;
ll key[MM];
pii val[MM];

int main(){
	for(int i = 0; i < MM; i++){
		key[i] = randl(0, LLONG_MAX/2);
		val[i] = {randl(0, INT_MAX), randl(0, INT_MAX)};
	}
	cout<<"start test"<<endl;
	
	for(int t = 0; t < 3; t++){
		START = chrono::system_clock::now();
		hashmap *mp = new hashmap();
		for(int i = 0; i < MM; i++){
			mp->update(key[i], val[i]);
		}
		END = chrono::system_clock::now();
		tot = END-START;
		cout<<"hashmap "<<tot.count()<<endl;
		delete mp;
		
		START = chrono::system_clock::now();
		__gnu_pbds::gp_hash_table<ll, pii> mp2;
		for(int i = 0; i < MM; i++){
			add(mp2[key[i]], val[i]);
		}
		END = chrono::system_clock::now();
		tot = END-START;
		cout<<"gp_hash_table "<<tot.count()<<endl;
		
		START = chrono::system_clock::now();
		unordered_map<ll, pii> mp3;
		for(int i = 0; i < MM; i++){
			add(mp3[key[i]], val[i]);
		}
		END = chrono::system_clock::now();
		tot = END-START;
		cout<<"unordered_map "<<tot.count()<<endl;
		
		//hashmap is 2.5 times faster than gp_hash_table, which is in turn 2.5 times faster than unordered_map
	}
	
	test.update(1, {2, 3});
	test.update(2, {4, 5});
	for(int i = 0; i < test.sz; i++){ //iterate through hash table
		print(i, test.key[i], test.val[i].first, test.val[i].second);
	}
}