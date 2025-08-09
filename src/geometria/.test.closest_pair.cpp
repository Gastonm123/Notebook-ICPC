// https://cses.fi/problemset/task/2194
 
#include <bits/stdc++.h>
using namespace std;
#define dprint(v) cout << #v "=" << v << endl //;)
#define forr(i, a, b) for (int i = (a); i < (b); i++)
#define forn(i, n) forr(i, 0, n)
#define dforn(i, n) for (int i = n - 1; i >= 0; i--)
#define forall(it, v) for (auto it = v.begin(); it != v.end(); ++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define fst first
#define snd second
#define mid(a,b) ((a+b)>>1)
#define all(v) begin(v),end(v)
#define mp make_pair
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
 
struct pt {
    ll x, y;
    pt () {}
    pt (ll _x, ll _y) : x(_x), y(_y) {}
    pt operator-(const pt o) const {
        return pt(x-o.x, y-o.y); }
    ll norm_sq() const {
        return x*x+y*y; }
};

ll INF=4e18;
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
 
int main() {
    iostream::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n; cin >> n;
    vector<pt> puntos(n);
    forn (i, n) {
        cin >> puntos[i].x >> puntos[i].y;
    }

    cout << closest(puntos) << endl;
}
