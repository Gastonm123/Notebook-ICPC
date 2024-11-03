tipo INF=8e18+1;
#define dist(a, b) ((a-b).norm_sq())
bool compy(pt a, pt b) {
    return mp(a.y,a.x)<mp(b.y,b.x); }
bool compx(pt a, pt b) {
    return mp(a.x,a.y)<mp(b.x,b.y); }
// los puntos deben estar ordenados por x
// inicialmente: l=0, r=sz(ps)
ll closest(vector<pt> &ps, int l, int r) {
    if (l == r-1) return INF;
    if (l == r-2) {
        sort(&ps[l], &ps[r], compy);
        return dist(ps[l], ps[l+1]); }
    int m = (l+r)/2, xm = ps[m].x;
    ll min_dist  = min(closest(ps, l, m),closest(ps, m, r));
    tipo delta = sqrt(min_dist);
    vector<pt> sorted(r-l);
    merge(&ps[l], &ps[m], &ps[m], &ps[r], &sorted[0], compy);
    copy(all(sorted), &ps[l]);
    vector<pt> strip;
    forr (i, l, r) {
        if (ps[i].x > int(xm-delta)
        && ps[i].x <= int(xm+delta)) {
            strip.pb(ps[i]);
        }
    }
    forn (i, sz(strip)) {
        forr (j, 1, 8) {
            if (i+j >= sz(strip)) break;
            if (dist(strip[i], strip[i+j]) < min_dist)
                min_dist = dist(strip[i], strip[i+j]);
        }
    }
    return min_dist;
}