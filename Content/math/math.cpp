#include <bits/stdc++.h>
using namespace std;

using T = long long;

template<class T> T gcd(T _a, T _b){return _b == 0 ? _a : gcd(_b, _a%_b);}
template<class T, class U> T fpow(T _base, U _pow, T _mod){_base %= _mod; T _x = 1; for(; _pow > 0; _pow >>= 1){ if(_pow&1) _x = _x*_base%_mod; _base = _base*_base%_mod;} return _x;}
template<class T> T divmod(T _a, T _b, T _mod){return _a*fpow(_b, _mod-2, _mod)%_mod;}

//mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
//mt19937_64 g((uint64_t) new char);
mt19937_64 g(0);
int randint(int l, int r){return uniform_int_distribution<int>(l, r)(g);}
long long randl(long long l, long long r){return uniform_int_distribution<long long>(l, r)(g);}
T randt(T a, T b){return uniform_int_distribution<T>(a, b)(g);}

T eea(T a, T b, T &x, T &y){
	if(a == 0){
		x = 0, y = 1;
		return b;
	}
	T x1, y1;
	T d = eea(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

bool diophantine(T a, T b, T c, T &x0, T &y0, T &g){
	g = eea(abs(a), abs(b), x0, y0);
	if(c % g)
		return 0;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0) x0 = -x0;
	if (b < 0) y0 = -y0;
	return 1;
}

void shift(T &x, T &y, T a, T b, T cnt){
	x += cnt * b;
	y -= cnt * a;
}

T diophantine_cnt(T a, T b, T c, T minx, T maxx, T miny, T maxy){
	T x, y, g;
	if(!diophantine(a, b, c, x, y, g))
		return 0;
	a /= g;
	b /= g;

	T sign_a = a > 0 ? 1 : -1;
	T sign_b = b > 0 ? 1 : -1;

	shift(x, y, a, b, (minx - x) / b);
	if(x < minx) shift(x, y, a, b, sign_b);
	if(x > maxx) return 0;
	T lx1 = x;

	shift(x, y, a, b, (maxx - x) / b);
	if(x > maxx) shift(x, y, a, b, -sign_b);
	T rx1 = x;

	shift(x, y, a, b, -(miny - y) / a);
	if(y < miny) shift(x, y, a, b, -sign_a);
	if(y > maxy) return 0;
	T lx2 = x;

	shift(x, y, a, b, -(maxy - y) / a);
	if(y > maxy) shift(x, y, a, b, sign_a);
	T rx2 = x;

	if(lx2 > rx2) swap(lx2, rx2);
	T lx = max(lx1, lx2);
	T rx = min(rx1, rx2);

	if(lx > rx) return 0;
	return (rx - lx) / abs(b) + 1;
}
