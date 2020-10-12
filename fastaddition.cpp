#include <bits/stdc++.h>
using namespace std;

template<class T> T fastaddition(T x,T y,T MOD){
    if(!y) return x;
    T t=fastaddition(fastaddition(x,y/2,MOD),y/2,MOD);
    if(y&1) return (t+1)%MOD;
    return t;
}


int main(){
    cin.tie(0)->sync_with_stdio(0);
    int a,b,mod;
    cin>>a>>b;
    cout<<fastaddition(a,b,mod);
    return 0;
}
/**

*/
