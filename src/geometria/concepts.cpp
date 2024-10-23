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

void sweep_space() {
    vector<Event> eventos; // puntos, segmentos, ...
    sort(eventos);         // sort por x, y, ...
    set<Info> estado;      // mantener la informacion ordenada
    forn(i, sz(eventos)) {
        Event &e = eventos[i];
        process(e, estado); // procesar un evento cambia el estado
        ans = actualizar(ans);
} }


