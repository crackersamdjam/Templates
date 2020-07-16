#include <bits/stdc++.h>
using namespace std;

#define gc getchar_unlocked

inline int readint(){
	int w=0,f=1;
	char ch=gc();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=gc();
	}
	while(ch>47&&ch<58){
		w=w*10+ch-48;
		ch=gc();
	}
	return w*f;
}

int main(){
	
	for(int i = 0; i < 5; i++)
		cout << readint() << endl;
	
	return 0;
}
