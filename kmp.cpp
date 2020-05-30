#include <bits/stdc++.h>
using namespace std;

string s, t;
vector<int> pre;

int main(){;
    while(getline(cin, s)){
        getline(cin, t);
        
        int sub = s.size();
        s = s+"#"+t;
        int n = s.size();
        
        pre.resize(n);
        pre[0] = 0;
        for(int i = 1; i < s.size(); i++){
            int j = pre[i-1];
            if(j and s[i] != s[j])
                j = pre[j-1];
            if(s[i] == s[j])
                j++;
            pre[i] = j;
            if(i-sub-sub >= 0 and pre[i] == sub)
                cout<<i-sub-sub<<' ';
        }
        cout<<'\n';
    }
    
    return 0;
}