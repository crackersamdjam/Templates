#include <bits/stdc++.h>
using namespace std;
using T = long long;
constexpr T mod = 1e9+7;

struct matrix{
    int n, m;
    vector<vector<T>> a;
    matrix(int _n = 0, int _m = 0){
        n = _n, m = _m;
        a.resize(n);
        for(int i = 0; i < n; i++)
            a[i].resize(m);
    }
};
matrix mul(matrix ma, matrix mb){
    matrix c(ma.n, mb.m);
    for(int i = 0; i < ma.n; i++){
        for(int j = 0; j < mb.m; j++){
            T t = 0;
            for(int k = 0; k < ma.m; k++)
                t = (t + ma.a[i][k] * mb.a[k][j]) % mod;
            c.a[i][j] = t;
        }
    }
    return c;
}

matrix fpow(matrix m, T exp){
    if(exp == 1)
        return m;
    matrix ret = fpow(m, exp/2);
    ret = mul(ret, ret);
    if(exp&1)
        ret = mul(ret, m);
    return ret;
}


int main(){
    int n; T k;
    cin >> n >> k;
    matrix a(n, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cin >> a.a[i][j];
    }
    a = fpow(a, k);
    T res = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            res += a.a[i][j];
            res %= mod;
        }
    }
    
    cout << res;
    
    return 0;
}