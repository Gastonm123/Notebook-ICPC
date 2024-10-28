struct Segment {
    Vector a, b;
    long double eval() const
    { // evaluar un segmento en una coordenada x
        assert(a.x != b.x || a.y != b.y);
        Vector a1 = a, b1 = b;
        if (a1.x > b1.x)
            swap(a1, b1);
        assert(x >= a1.x && x <= b1.x);
        if (x == a1.x)
            return a1.y;
        if (x == b1.x)
            return b1.y;
        Vector ab = b1 - a1;
        return a1.y + (x - a1.x) * (ab.y / ab.x);
    }
    bool operator<(Segment o) const
    { // orden de segmentos en un punto (x=cte)
        return (eval() - o.eval()) < -1e-13;
    }
};

// LOWER ENVELOPE
const ll is_query = -(1LL<<62);
struct Line {
    ll m, b;
    mutable multiset<Line>::iterator it;
    const Line *succ(multiset<Line>::iterator it) const;
    bool operator<(const Line & rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line *s = succ(it);
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b > (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> {
    bool bad(iterator y) {
        iterator z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b >= z->b;
        }
        iterator x = prev(y);
        if (z == end()) return y->m == x->m && y->b >= x->b;
        return (x->m-z->m)*(z->b-y->b) >= (z->b-x->b)*(y->m-z->m);
    }
    iterator next(iterator y) {return ++y;}
    iterator prev(iterator y) {return --y;}
    void insert_line(ll m, ll b) {
        iterator y = insert((Line) {m, b});
        y->it = y;
        if (bad(y)) {erase(y); return;}
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll eval(ll x) {
        Line l = *lower_bound((Line) {x, is_query});
        return l.m * x + l.b;
    }
} h;
const Line *Line::succ(multiset<Line>::iterator it) const {
    return (++it==h.end() ? NULL : &*it); }
