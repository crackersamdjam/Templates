#include <bits/stdc++.h>
using namespace std;

using T = long long;

T gcd(T gcd_a, T gcd_b){return gcd_b == 0 ? gcd_a : gcd(gcd_b, gcd_a % gcd_b);}
T fpow(T fpow_b, T fpow_exp, T fpow_mod){if(fpow_exp == 0) return 1;T t = fpow(fpow_b,fpow_exp/2,fpow_mod);if(fpow_exp&1) return t*t%fpow_mod*fpow_b%fpow_mod;return t*t%fpow_mod;}
T divmod(T divmod_i, T divmod_j, T divmod_mod){divmod_i%=divmod_mod,divmod_j%=divmod_mod;return divmod_i*fpow(divmod_j,divmod_mod-2,divmod_mod)%divmod_mod;}

mt19937 g1(time(0));
int randint(int a, int b){return uniform_int_distribution<int>(a, b)(g1);}
T randlong(T a,T b){return uniform_int_distribution<T>(a, b)(g1);}

T exgcd(T a, T b, T &x, T &y){
	if(a == 0){
		x = 0, y = 1;
		return b;
	}
	T x1, y1;
	T d = exgcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

bool diophantine(T a, T b, T c, T &x0, T &y0, T &g){
	g = exgcd(abs(a), abs(b), x0, y0);
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
