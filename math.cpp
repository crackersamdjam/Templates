#include <bits/stdc++h>

ll pow(ll a, ll b, ll m) {
    a %= m;
    ll ret = 1;
    while (b > 0) {
        if (b & 1) ret = ret * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return ret;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int gcd(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool diophantine(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift(int & x, int & y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

int diophantine_all(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!diophantine(a, b, c, x, y, g)) return 0;
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift(x, y, a, b, (minx - x) / b);
    if (x < minx) shift(x, y, a, b, sign_b);
    if (x > maxx) return 0;
    int lx1 = x;

    shift(x, y, a, b, (maxx - x) / b);
    if (x > maxx) shift(x, y, a, b, -sign_b);
    int rx1 = x;

    shift(x, y, a, b, -(miny - y) / a);
    if (y < miny) shift(x, y, a, b, -sign_a);
    if (y > maxy) return 0;
    int lx2 = x;

    shift(x, y, a, b, -(maxy - y) / a);
    if (y > maxy) shift(x, y, a, b, sign_a);
    int rx2 = x;

    if (lx2 > rx2) swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx) return 0;
    return (rx - lx) / abs(b) + 1;
}