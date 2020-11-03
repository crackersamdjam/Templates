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

template<class T, int SZ> struct bit{
	T bit[SZ];
	void up(int i, T v){
		for(; i < SZ; i += i&-i)
			bit[i] += v;
	}
	T qu(int i){
		static T v;
		for(v = 0; i; i -= i&-i)
			v += bit[i];
		return v;
	}
};

template<class T, int SZ> struct rbit{
	bit<T, SZ> T1, T2;
	T qu(int i){
		return i*T1.qu(i)-T2.qu(i);
	}
	T qu(int l, int r){
		return qu(r)-qu(l-1);
	}
	void up(int l, int r, T v){
		T1.up(l, v);
		T1.up(r+1, -v);
		T2.up(l, v*(l-1));
		T2.up(r+1, -v*r);
	}
	void up(int l, T v){
		up(l, l, v);
	}
};

rbit<int, 10> T;

int main(){
	T.up(3, 5, 2);
	T.up(4, 8, 6);
	
	print(T.qu(3, 5));
	
	for(int i = 1; i < 10; i++)
		cout<<T.qu(i, i)<<' ';
}
