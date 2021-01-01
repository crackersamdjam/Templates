// https://dmoj.ca/problem/ccc20s3
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
const int MM = 2e5+5, N = 2;

mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
int randint(int l, int r){return uniform_int_distribution<int>(l, r)(g);}
long long randl(long long l, long long r){return uniform_int_distribution<long long>(l, r)(g);}

const ll base = randint(4e5, 1e9), mod[] = {1685518853, 1494318097};

int n, m, ans;
ll h[N][MM], p[N][MM];
char s[MM], t[MM];
vector<int> cnts(26), cntt(26);
set<array<ll, 2>> st;

int main(){
	scanf("%s %s", s+1, t+1);
	n = strlen(s+1);
	m = strlen(t+1);
	for(int i = 1; i <= n; i++)
		cnts[s[i]-'a']++;

	for(int j = 0; j < N; j++)
		p[j][0] = 1;

	for(int i = 1; i <= m; i++){
		cntt[t[i]-'a']++;
		if(i-n > 0) cntt[t[i-n]-'a']--;
		for(int j = 0; j < N; j++){
			p[j][i] = p[j][i-1]*base%mod[j];
			h[j][i] = (h[j][i-1]*base + t[i])%mod[j];
		}
		if(cnts == cntt){
			array<ll, N> a;
			for(int j = 0; j < N; j++){
				a[j] = (h[j][i]-h[j][i-n]*p[j][n])%mod[j];
				if(a[j] < 0) a[j] += mod[j];			
			}
			st.insert(a);
		}
	}
	printf("%ld\n", size(st));
}