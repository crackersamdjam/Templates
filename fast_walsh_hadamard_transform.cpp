#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> int size(const T &x){return int(x.size());}
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
namespace fwht{
	using T = int;
	const T w = 1, x = 1, y = 1, z = 0;
	const T det = w*z-x*y;
	// calculate transform matrix http://serbanology.com/show_article.php?art=A%20Bitwise%20Convolution%20Tutorial
	// fwht::mul in input vectors A, B and output vector C, v[i] = [# of ways / probability/ any value of type T] to get a mask of i
	// fwht can be used for bitwise operators
	// for xor: w,x,y,z = 1,1,1,-1
	// for or: w,x,y,z = 1,1,1,0
	// for and: I didn't check yet
	
	void go(vector<T> &v){
		int n = size(v);
		for(int len = 1; len < n; len *= 2){
			for(int pos = 0; pos < n; pos += len*2){
				for(int i = 0; i < len; i++){
					// replace values v[pos+i] v[pos+1+len] with their product with T_2
					T a = v[pos+i];
					T b = v[pos+i+len];
					v[pos+i] = w*a+x*b;
					v[pos+i+len] = y*a+z*b;
				}
			}
		}
	}
	void invgo(vector<T> &v){
		int n = size(v);
		for (int len = 1; len < n; len*= 2) {
			for (int pos = 0; pos < n; pos+= len * 2) {
				for (int i = 0; i < len; ++i) {
					// replace values v[pos+i] v[pos+1+len] with their product with the inverse of T_2
					T a = v[pos+i];
					T b = v[pos+i+len];
					v[pos+i] = (z*a-y*b)/det;
					v[pos+i+len] = (w*b-x*a)/det;
				}
			}
		}
	}
	void mul(vector<T> &va, vector<T> &vb){
		int n = size(va)+size(vb)-1;
		while(n&(n-1)) n++;
		va.resize(n), vb.resize(n);
		go(va);
		go(vb);
		for(int i = 0; i < n; i++)
			va[i] *= vb[i];
		invgo(va);
	}
};

int main(){
	vector<int> a = {1, 2, 3}, b = {3, 4};
	fwht::mul(a, b);
	for(int i: a)
		print(i);
}
