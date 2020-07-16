#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar(x)
template<typename T> void scan(T &x){x = 0;register bool _=0;register T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){register bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
typedef long long ll;
const int MM = 1e6+5, N = 5;
ll base = 131, mod[] = {1685518853, 1494318097, (ll)1e9+9, (ll)1e9+7, (ll)1e9+37};

int n, k;
ll h[N][MM], p[N][MM];
char str[MM];

ll get(int j, int l, int r){
	ll hs = (h[j][r] - h[j][l]*p[j][r-l]) % mod[j];
	if(hs < 0)
		hs += mod[j];
	return hs;
}

bool check(int la, int ra, int lb, int rb){
	for(int j = 0; j < N; j++){
		if(get(j, la, ra) != get(j, lb, rb))
			return 0;
	}
	return 1;
}

int main(){
	
	scanf("%s %d", str+1, &k);
	
	n = strlen(str+1);
	
	for(int j = 0; j < N; j++){
		p[j][0] = 1;
		for(int i = 1; i <= n; i++){
			p[j][i] = p[j][i-1]*base % mod[j];
			h[j][i] = (h[j][i-1]*base + str[i]) % mod[j];
		}
	}
	
	int st = 1;
	for(int i = 1; i <= n-k+1; i++){
		
		if(str[i] < str[st]){
			st = i;
			continue;
		}
		if(str[i] > str[st])
			continue;
		
		int l = 0, m, r = k;
		while(l <= r){
			m = (l+r)/2;
			if(check(i-1, i+m, st-1, st+m))
				l = m+1;
			else
				r = m-1;
		}
		if(l < k && str[i+l] < str[st+l])
			st = i;
	}
	
	for(int i = st; i < st+k; i++)
		pc(str[i]);
	
	pc(10);
	
	return 0;
}