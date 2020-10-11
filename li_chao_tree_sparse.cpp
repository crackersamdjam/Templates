template <typename T> struct Line {
    T m, b;
    Line(T m0, T b0) : m(m0), b(b0) {}
    T eval(T x) { return x * m + b; }
};
using line = Line<ll>; // Define!!!
const ll MINX = -1e6, MAXX = 1e6; // Define!!!
struct LiChao { // Just *-1 if you want to do max lol
    struct Node {
        Node *l = nullptr, *r = nullptr;
        line val{0, LLINF};
        Node(Node *l0, Node *r0, line v0) : l(l0), r(r0), val(v0) {}
    };
    Node *rt = nullptr;
    void _insert(line ln, Node *&n, ll l, ll r) {
        if (l > r) return;
        if (!n) {
            n = new Node(nullptr, nullptr, ln);
            return;
        }
        ll mid = (l + r) / 2;
        bool lDom = ln.eval(l) < n->val.eval(l), mDom = ln.eval(mid) < n->val.eval(mid);
        if (mDom) swap(ln, n->val);
        if (l == r) return; // base case
        if (lDom != mDom) _insert(ln, n->l, l, mid);
        else _insert(ln, n->r, mid + 1, r);
    }
    void insert(line ln) { _insert(ln, rt, MINX, MAXX); }
    ll _query(ll x, Node *n, ll l, ll r) {
        if (!n) return LLINF;
        ll res = n->val.eval(x), mid = (l + r) / 2;
        if (l != r) {
            if (x < mid) res = min(res, _query(x, n->l, l, mid));
            else res = min(res, _query(x, n->r, mid + 1, r));
        }
        return res;
    }
    ll query(ll x) { return _query(x, rt, MINX, MAXX); }
};


