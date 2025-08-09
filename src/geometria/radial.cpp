struct Radial {
    pt o;
    Radial(pt _o) : o(_o) {}
    int cuad(pt p) {
        if (p.x>0 && p.y>=0) return 1;
        if (p.x<=0 && p.y>0) return 2;
        if (p.x<0 && p.y<=0) return 3;
        if (p.x>=0 && p.y<0) return 4;
        assert(p.x == 0 && p.y == 0);
        return 0; // origen < todos
    }
    bool comp(pt p, pt q) {
        int c1 = cuad(p), c2 = cuad(q);
        if (c1 == c2) return p%q>EPS;
        return c1 < c2;
    }
    bool operator()(const pt &p, const pt &q) const {
        return comp(p-o,q-o);
    }
};