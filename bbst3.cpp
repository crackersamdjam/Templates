#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define complete_unique(a) a.erase(unique(a.begin(),a.end()),a.end())
#define all(a) a.begin(),a.end()
#define println printf("\n");
#define readln(x) getline(cin,x);
#define pb push_back
#define endl "\n"
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
#define mp make_pair
#define fastio cin.tie(0); cin.sync_with_stdio(0);

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unordered_map<int,int> umii;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef pair<ll,ll> pll;
typedef pair<int,pii> triple;
typedef int8_t byte;

mt19937 g1(time(0));

int randint(int a, int b){return uniform_int_distribution<int>(a, b)(g1);}
ll randlong(ll a,ll b){return uniform_int_distribution<long long>(a, b)(g1);}

ll gcd(ll a, ll b){return b == 0 ? a : gcd(b, a % b);}
ll lcm(ll a, ll b){return a*b/gcd(a,b);}
ll fpow(ll  b, ll exp, ll mod){if(exp == 0) return 1;ll t = fpow(b,exp/2,mod);if(exp&1) return t*t%mod*b%mod;return t*t%mod;}
ll divmod(ll i, ll j, ll mod){i%=mod,j%=mod;return i*fpow(j,mod-2,mod)%mod;}

template<typename T>
struct node{ //if you want sum for ints, change sum to long long
    T val,sum; int sz; ll prior;
    node *l,*r;
    node(T v){
        val = v, sz = 1, sum = val;
        prior = randlong(1,1e18);
        l = r = 0;
    }
};

template<typename T>
struct SMTreap{
    node<T> *rt;
    
    inline int gsz(node<T> *&n){return n?n->sz:0;}
    inline void upd_sz(node<T> *&n){if(n)n->sz=gsz(n->l)+gsz(n->r)+1;}
    inline T gsum(node<T> *&n){return n?n->sum:0;}
    inline void upd_sum(node<T> *&n){if(n)n->sum=gsum(n->l)+gsum(n->r)+n->sum;}
    inline void upd(node<T> *&n){upd_sz(n);upd_sum(n);}
    
    void split(node<T> *n, T key, node<T> *&l, node<T> *&r){
        if(!n) l = r = 0;
        else if(key < n->val) split(n->l,key,l,n->l), r = n;
        else split(n->r,key,n->r,r), l = n;
        upd(n);
    }
    void merge(node<T> *&n, node<T> *l, node<T> *r){
        if(!l || !r) n = l?l:r;
        else if(l->prior > r->prior) merge(l->r,l->r,r), n = l;
        else merge(r->l,l,r->l), n = r;
        upd(n);
    }
    void insert(node<T> *&n, node<T> *v){
        if(!n) n = v;
        else if(v->prior > n->prior) split(n,v->val,v->l,v->r), n = v;
        else insert(v->val<n->val?n->l:n->r,v);
        upd(n);
    }
    void erase(node<T> *&n, T v){
        if(!n) return;
        if(n->val == v) merge(n,n->l,n->r);
        else erase(v<n->val?n->l:n->r,v);
        upd(n);
    }
    T find_by_order(node<T> *&n, int idx){
        if(gsz(n->l)+1 == idx) return n->val;
        else if(gsz(n->l) >= idx) return find_by_order(n->l,idx);
        return find_by_order(n->r,idx-gsz(n->l)-1);
    }
    bool contains(node<T> *&n, T v){
        if(!n) return false;
        if(n->val == v) return true;
        if(n->val < v) return contains(n->r,v);
        return contains(n->l,v);
    }
    int num_less(node<T> *&n, T v){
        if(!n) return 0;
        if(n->val < v) return gsz(n->l)+1+num_less(n->r,v);
        return num_less(n->l,v);
    }
    void print(){
        for(int i=1; i<=gsz(rt); i++)
            printf("%d ",find_by_order(rt,i));
        printf("\n");
    }
};

int len,num_q,xx;
SMTreap<int> s;

int main(){
    scanf("%d %d",&len,&num_q);
    for(int i=1; i<=len; i++){
        int a; scanf(" %d",&a);
        s.insert(s.rt,new node<int>(a));
    }
    for(int i=1; i<=num_q; i++){
        char op; int v; scanf(" %c %d",&op,&v); v^=xx;
        if(op == 'I') s.insert(s.rt,new node<int>(v));
        else if(op == 'R') s.erase(s.rt,v);
        else if(op == 'S') printf("%d\n",xx=s.find_by_order(s.rt,v));
        else printf("%d\n",xx=(s.contains(s.rt,v)?s.num_less(s.rt,v)+1:-1));
    }
    s.print();
}
