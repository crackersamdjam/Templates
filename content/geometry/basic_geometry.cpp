#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using T = double;

constexpr const T EPS = 1e-9;
bool lt(T a, T b) { return a + EPS < b; }
bool le(T a, T b) { return !lt(b, a); }
bool gt(T a, T b) { return lt(b, a); }
bool ge(T a, T b) { return !lt(a, b); }
bool eq(T a, T b) { return !lt(a, b) && !lt(b, a); }
bool ne(T a, T b) { return lt(a, b) || lt(b, a); }
int sgn(T a) { return lt(a, 0) ? -1 : lt(0, a) ? 1 : 0; }
struct eps_lt { bool operator () (T a, T b) const { return lt(a, b); } };
struct eps_le { bool operator () (T a, T b) const { return !lt(b, a); } };
struct eps_gt { bool operator () (T a, T b) const { return lt(b, a); } };
struct eps_ge { bool operator () (T a, T b) const { return !lt(a, b); } };
struct eps_eq {
	bool operator () (T a, T b) const { return !lt(a, b) && !lt(b, a); }
};
struct eps_ne {
	bool operator () (T a, T b) const { return lt(a, b) || lt(b, a); }
};

#define x real()
#define y imag()
#define ref const pt &
using pt = complex<T>;

istream &operator >> (istream &stream, pt &p) {
	T X, Y; stream >> X >> Y; p = pt(X, Y); return stream;
}
ostream &operator << (ostream &stream, ref p) {
	return stream << p.x << ' ' << p.y;
}
bool operator < (ref a, ref b) {
	return eq(a.x, b.x) ? lt(a.y, b.y) : lt(a.x, b.x);
}
bool operator <= (ref a, ref b) { return !(b < a); }
bool operator > (ref a, ref b) { return b < a; }
bool operator >= (ref a, ref b) { return !(a < b); }
bool operator == (ref a, ref b) { return !(a < b) && !(b < a); }
bool operator != (ref a, ref b) { return a < b || b < a; }
struct pt_lt { bool operator () (ref a, ref b) const { return a < b; } };
struct pt_le { bool operator () (ref a, ref b) const { return !(b < a); } };
struct pt_gt { bool operator () (ref a, ref b) const { return b < a; } };
struct pt_ge { bool operator () (ref a, ref b) const { return !(a < b); } };
struct pt_eq {
	bool operator () (ref a, ref b) const { return !(a < b) && !(b < a); }
};
struct pt_ne {
	bool operator () (ref a, ref b) const { return a < b || b < a; }
};
// abs gets polar distance, arg gets polar angle
T dot(ref a, ref b) { return a.x * b.x + a.y * b.y; }
T cross(ref a, ref b) { return a.x * b.y - a.y * b.x; }
T norm(ref a) { return dot(a, a); }
T distSq(ref a, ref b) { return norm(b - a); }
T dist(ref a, ref b) { return abs(b - a); }
T ang(ref a, ref b) { return arg(b - a); }
// sign of ang, area2, ccw: 1 if counterclockwise, 0 if collinear,
//   -1 if clockwise
T ang(ref a, ref b, ref c) {
	return remainder(ang(b, a) - ang(b, c), 2 * acos(T(-1)));
}
// twice the signed area of triangle a, b, c
T area2(ref a, ref b, ref c) { return cross(b - a, c - a); }
int ccw(ref a, ref b, ref c) { return sgn(area2(a, b, c)); }
// a rotated theta radians around p
pt rot(ref a, ref p, T theta) {
	return (a - p) * pt(polar(T(1), theta)) + p;
}
// rotated 90 degrees ccw
pt perp(ref a) { return pt(-a.y, a.x); }
