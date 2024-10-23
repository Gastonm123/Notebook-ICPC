struct Comp {
    pt o, v;
    Comp(pt _o, pt _v) : o(_o), v(_v) {}
    bool half(pt p) {
        // assert(!(p.x == 0 && p.y == 0));
        return (v ^ p) < 0 || 
            ((v ^ p) == 0 && (v * p) < 0); }
    bool operator()(pt a, pt b) {
        return mp(half(a - o), 0ll) 
            < mp(half(b - o), ((a - o) ^ (b - o))); }
};

// no debe haber un punto igual al pivot en el rango [b, e]
// en general usar la direccion (1,0)
void radial_sort(vector<pt>::iterator b,
    vector<pt>::iterator e, pt pivot, pt dir) {
    sort(b, e, Comp(pivot, dir)); }