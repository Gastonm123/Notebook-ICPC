// https://cses.fi/problemset/task/2193

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
    pt() {}
    pt(ll _x, ll _y) : x(_x), y(_y) {}
    pt operator-(pt o) const {
        return pt(x-o.x, y-o.y);
    }
    ll operator^(pt o) const {
        return x*o.y-y*o.x;
    }
};

struct pol {
    int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
    double area() {
        ll a = 0;
        forr (i, 1, sz(p)-1) {
            a += (p[i]-p[0])^(p[i+1]-p[0]);
        }
        return abs(a)/2;
    }
};

int main() {
    int n; cin >> n;

    vector<pt> ps(n); forn  (i, n) cin >> ps[i].x >> ps[i].y;
    pol p(ps);
    // teorema de Pick
    ll a = p.area();
    ll borde = 0;
    forn (i, n) {
        if (i < n-1) {
            pt d = ps[i+1]-ps[i];
            borde += __gcd(abs(d.x), abs(d.y));
        }
        else {
            pt d = ps[0] - ps[i];
            borde += __gcd(abs(d.x), abs(d.y));
        }
    }
    cout << (a+2-borde)/2 << " " << borde << endl;
}