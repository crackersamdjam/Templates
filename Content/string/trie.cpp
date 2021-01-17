#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;register bool _=0;register T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){register bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;

struct node{
	char n;
	map<char, node*> ch;
	node(int nn):n(nn){}
	~node(){
		for(auto i: ch)
			delete i.second;
	}
};

int main(){
	
	int T, N;
	scan(T);
	for(int tc = 1; tc <= T; tc++){
		int tot = 0;
		node *rt = new node('a');
		scan(N);
		
		for(int t = 0; t < N; t++){
			string str;
			cin >> str;
			int ans = str.size();
			node *pre = rt;
			for(int i = 0; i < str.size(); i++){
				
				if(pre->ch.find(str[i]) == pre->ch.end()){
					ans = min(ans, i+1);
					pre->ch[str[i]] = new node(str[i]);
				}
				pre = pre->ch[str[i]];
			}
			
			tot += max(ans, 1);
		}
		
		printf("Case #%d: %d\n", tc, tot);
		
		delete rt;
	}
	
	return 0;
}
