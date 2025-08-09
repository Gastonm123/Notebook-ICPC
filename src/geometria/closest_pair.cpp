#define dist(a, b) ((a-b).norm_sq())
bool sortx(pt a, pt b) {
    return mp(a.x,a.y)<mp(b.x,b.y); }
bool sorty(pt a, pt b) {
    return mp(a.y,a.x)<mp(b.y,b.x); }
ll closest(vector<pt> &ps, int l, int r) {
    if (l == r-1) return INF;
    if (l == r-2) {
        if (sorty(ps[l+1], ps[l]))
            swap(ps[l+1], ps[l]);
        return dist(ps[l], ps[l+1]);
    }
    int m = (l+r)/2; ll xm = ps[m].x;
    ll min_dist = min(closest(ps, l, m),closest(ps, m, r));
    vector<pt> left(&ps[l], &ps[m]), right(&ps[m], &ps[r]);
    merge(all(left), all(right), &ps[l], sorty);
    ll delta = ll(sqrt(min_dist));
    vector<pt> strip;
    forr (i, l, r) if (ps[i].x>=xm-delta&&ps[i].x<=xm+delta)
        strip.pb(ps[i]);
    forn (i, sz(strip)) forr (j, 1, 8) {
        if (i+j >= sz(strip)) break;
        min_dist = min(min_dist, dist(strip[i], strip[i+j]));
    }
    return min_dist;
}
ll closest(vector<pt> &ps) { // devuelve dist^2
    sort(all(ps), sortx);
    return closest(ps, 0, sz(ps));
}