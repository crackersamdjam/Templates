// overkill sol to https://atcoder.jp/contests/abc097/tasks/arc097_a
// more functions https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Heavy/SuffixAutomaton.h

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct st{
    int len, link;
    map<char, int> adj;
};
const int MM = 100002;
st a[MM*2];
int sz, last;
ll cnt[MM];

void init(){
    a[0].len = 0;
    a[0].link = -1;
    sz++;
    last = 0;
}

void extend(char c){
    int cur = sz++;
    a[cur].len = a[last].len + 1;
    int p = last;
    while (p != -1 && !a[p].adj.count(c)) {
        a[p].adj[c] = cur;
        p = a[p].link;
    }
    if (p == -1) {
        a[cur].link = 0;
    } else {
        int q = a[p].adj[c];
        if (a[p].len + 1 == a[q].len) {
            a[cur].link = q;
        } else {
            int clone = sz++;
            a[clone].len = a[p].len + 1;
            a[clone].adj = a[q].adj;
            a[clone].link = a[q].link;
            while (p != -1 && a[p].adj[c] == q) {
                a[p].adj[c] = clone;
                p = a[p].link;
            }
            a[q].link = a[cur].link = clone;
        }
    }
    last = cur;
}

ll getsize(int x) {
    if (cnt[x]) return cnt[x];
    cnt[x] = 1;
    for(auto i: a[x].adj){
        cnt[x] += getsize(i.second);
    }
    return cnt[x];
}

string kth(int cur, int k){
    assert(k < cnt[cur]);
    if(!k) return ""; //lexographically least
    k--;
    for(auto i: a[cur].adj){
        if(k < cnt[i.second])
            return i.first+kth(i.second, k);
        k -= cnt[i.second];
    }
    assert(0);
    return "";
}

int main(){
    string s; int k;
    cin >> s >> k;
    init();
    for(auto c: s)
        extend(c);
    getsize(0);
    cout << kth(0, k);
    
    return 0;
}
