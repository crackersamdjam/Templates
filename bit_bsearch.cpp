// https://codeforces.com/blog/entry/61364
// lowest n where [1, n] has sum >= k
// bit2 is a sum of values to output
// https://dmoj.ca/problem/lkp18c2p5

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
using ll = long long;
const int MM = 1e5+5;

ll bit[MM];
int bit2[MM];

void update(int i, ll v, int c){
	for(; i < MM; i += i&-i)
		bit[i] += v, bit2[i] += c;
}

int eval(int i){
	int ret = 0;
	for(; i; i -= i&-i)
		ret += bit2[i];
	return ret;
}

int query(ll k){
	int id = 0, ret = 0;
	for(int i = 20; i >= 0; i--){
		int j = 1<<i;
		if(id+j < MM and bit[id+j] < k){
			k -= bit[id+j];
			// ret += bit2[id+j];
			id += j;
		}
	}
	if(id == MM-1)
		return -1; //not enough to reach value >= k
	return eval(id+1); // id+1 because id gives < k
}

int main(){
	update(1, 5, 1);
	update(2, 3, 2);
	update(3, 1, 1);
	
	print(query(7), query(8), query(9), query(10));
}