// https://codeforces.com/gym/104252/problem/G
 
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

double INF=8e18+1;
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
    double delta = sqrt(min_dist);
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
 
int main() {
    iostream::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n; cin >> n;
    vector<pt> puntos(n);
    forn (i, n) {
        cin >> puntos[i].x >> puntos[i].y;
    }

    sort(all(puntos), compx);
    cout << closest(puntos, 0, sz(puntos)) << endl;
}
