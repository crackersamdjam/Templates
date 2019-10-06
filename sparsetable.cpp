#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MN = 5e4 + 5, LN = 20;
int N, Q, spt[MN][LN];

int query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return min(spt[l][k], spt[r - (1 << k) + 1][k]);
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> spt[i][0];
    for (int j = 1; (1 << j) <= N; j++) {
        for (int i = 1; i + (1 << j) - 1 <= N; i++) {
            spt[i][j] = min(spt[i][j - 1], spt[i + (1 << (j - 1))][j - 1]);
        }
    }
    return 0;
}