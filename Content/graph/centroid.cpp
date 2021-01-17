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
using ll = long long;
const int MM = 2e5+5;

int n;
ll a[MM], sz[MM], total;
vector<int> adj[MM], vec;

// gets sizes and pushes centroid(s) into vec
ll getsz(int cur, int pre){
	bool b = 1;
	sz[cur] = a[cur];
	for(int u: adj[cur]){
		if(u != pre){
			sz[cur] += getsz(u, cur);
			if(sz[u] > total/2)
				b = 0;
		}
	}
	if(b and ((total - sz[cur]) <= total/2))
		vec.push_back(cur);
	return sz[cur];
}

int main(){
	scan(n);
	//read populations into a[]
	//read graph into adj
	getsz(1, 0);
	
	printf("centroids are:\n");
	for(int i: vec)
		printf("%d ", i);
}
// this code finds (one or both) centroids based on population values