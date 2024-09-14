struct Point
{
    double x, y;
    double Point::operator*(const Point &o) const {
        return x * o.x + y * o.y; }
    double Point::operator^(const Point &o) const {
        return x * o.y - y * o.x; }
    Point Point::operator-(const Point &o) const {
        return {x - o.x, y - o.y}; }
    Point Point::operator+(const Point &o) const {
        return {x + o.x, y + o.y}; }
    Point Point::operator*(const double &u) const {
        return {x * u, y * u}; }
    Point Point::operator/(const double &u) const {
        return {x / u, y / u}; }
    double Point::norm_sq() const {
        return x * x + y * y; }
    double Point::norm() const {
        return sqrt(x * x + y * y); }
};

struct Comp {
    Vector o, v;
    Comp(Vector _o, Vector _v) : o(_o), v(_v) {}
    bool half(Vector p) {
        assert(!(p.x == 0 && p.y == 0));
        return (v ^ p) < 0 || ((v ^ p) == 0 && (v * p) < 0);
    }
    bool operator()(Vector a, Vector b) {
        return mp(half(a - o), 0ll) < mp(half(b - o), ((a - o) ^ (b - o)));
    }
};

struct Segment {
    Vector a, b;
    long double eval() const
    { // funcion auxiliar para ordenar segmentos
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

bool ccw(const Point &a, const Point &m, const Point &b) {
    return ((a - m) ^ (b - m)) > EPS; }

bool collinear(const Point &a, const Point &b, const Point &c) {
    return fabs((b - a) ^ (c - a)) < EPS; }

double dist_sq(const Point &a, const Point &b) {
    return (a - b).norm_sq(); }

double dist(const Point &a, const Point &b) {
    return (a - b).norm(); }

bool in_segment(const Point &p, const Point &b, const Point &c) {
    return fabs(dist_sq(p, b) + dist_sq(p, c) - dist_sq(b, c)) < EPS;
}

double angle(const Point &a, const Point &m, const Point &b) {
    Point ma = a - m, mb = b - m;
    return atan2(ma ^ mb, ma * mb);
}

void sweep_space() {
    vector<Event> eventos; // puntos, segmentos, ...
    sort(eventos);         // sort por x, y, ...
    set<Info> estado;      // mantener la informacion ordenada
    forn(i, sz(eventos)) {
        Event &e = eventos[i];
        process(e, estado); // procesar un evento cambia el estado
        ans = actualizar(ans);
    }
}